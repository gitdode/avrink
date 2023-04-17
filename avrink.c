/*
 * avrink.c
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * Experimental project to drive an E-Ink display with an SSD1680 driver.
 *
 * Created on: 26.03.2023
 *     Author: torsten.roemer@luniks.net
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "pins.h"
#include "usart.h"
#include "spi.h"
#include "sram.h"
#include "eink.h"
#include "unifont.h"
#include "bitmaps.h"
#include "utils.h"

/* Timer0 interrupts per second */
#define INTS_SEC  F_CPU / (64UL * 255)

static volatile uint16_t ints = 0;

static bool once = false;

ISR(TIMER0_COMPA_vect) {
    ints++;
}

/**
 * Sets up the pins.
 */
static void initPins(void) {
    // set LED pin as output pin
    DDR_LED |= (1 << PIN_LED);

    // set MOSI and SCK as output pin
    DDR_SPI |= (1 << PIN_MOSI);
    DDR_SPI |= (1 << PIN_SCK);
    // pull SS (ensure master) and MISO high
    PORT_SPI |= (1 << PIN_SS);
    PORT_SPI |= (1 << PIN_MISO);

    // set SRAM CS pin as output pin
    DDR_SRDI |= (1 << PIN_SRCS);

    // set display CS, D/C and RST pin as output pin
    DDR_SRDI |= (1 << PIN_ECS);
    DDR_SRDI |= (1 << PIN_DC);
    DDR_SRDI |= (1 << PIN_RST);

    // enable pullup on all output pins
    PORT_SRDI |= (1 << PIN_SRCS);
    PORT_SRDI |= (1 << PIN_ECS);
    PORT_SRDI |= (1 << PIN_DC);
    PORT_SRDI |= (1 << PIN_RST);

    // set display BUSY pin as input pin
    DDR_SRDI &= ~(1 << PIN_BUSY);
}

/**
 * Enables SPI master mode.
 */
static void initSPI(void) {
    SPCR |= (1 << SPR0);
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);
}

/**
 * Sets up the timer.
 */
static void initTimer(void) {
    // timer0 clear timer on compare match mode, TOP OCR0A
    TCCR0A |= (1 << WGM01);
    // timer0 clock prescaler/64/255 ~ 61 Hz @ 1 MHz
    TCCR0B |= (1 << CS01) | (1 << CS00);
    OCR0A = 255;

    // enable timer0 compare match A interrupt
    TIMSK0 |= (1 << OCIE0A);
}

/**
 * Turns the LED on.
 */
static void ledOn(void) {
    PORT_LED |= (1 << PIN_LED);
}

/**
 * Turns the LED off.
 */
static void ledOff(void) {
    PORT_LED &= ~(1 << PIN_LED);
}

/**
 * Just testing.
 */
static void sramFun(void) {
    uint8_t status = sramReadStatus();
    printByte(status);

    char *easter = "hello easter bunny!";
    size_t written = sramWriteString(0x123, easter);

    char bunny[written + 1]; // add one for null terminator
    sramReadString(0x123, bunny, sizeof (bunny));

    char buf[strlen(bunny) + 3];
    snprintf(buf, sizeof (buf), "%s\r\n", bunny);
    printString(buf);
}

/**
 * Copy image data from SRAM to display.
 * TODO write to display while reading from SRAM in sequential mode
 */
static void sramToDisplay(void) {
    uint16_t bytes = DISPLAY_WIDTH * DISPLAY_H_BYTES;

    for (uint16_t i = 0; i < bytes; i++) {
        uint8_t byte = sramRead(i);
        // remove negation for dark mode :)
        imageWrite(~byte);
    }

    printString("done copying from SRAM to display\r\n");
}

/**
 * Fills the frame (SRAM) with the given byte, i.e. 0x00 for all white
 * and 0xff for all black.
 * @param byte
 */
static void setFrame(uint8_t byte) {
    uint16_t bytes = DISPLAY_WIDTH * DISPLAY_H_BYTES;
    
    for (int i = 0; i < bytes; i++) {
        sramWrite(i, byte);
    }
}

/**
 * Writes the given byte at the given index for the given bitmap height
 * to its address/location. 
 * @param index
 * @param address
 * @param height
 * @param byte
 */
static void bufferByte(uint16_t index, uint16_t *address, uint16_t height, 
        uint8_t byte) {
    if (index % height == 0) {
        if (index > 0) {
            *address -= height / 8 - 1;
        }
    } else if (index % 8 == 0) {
        *address += 8 * DISPLAY_H_BYTES + 1;
    }

    sramWrite(*address, byte);
    *address -= DISPLAY_H_BYTES;
}

/**
 * Writes the given bitmap stored in program memory with the given width  
 * and height to the given row and column to SRAM. Width and height must be 
 * multiples of 8.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param bitmap
 * @param width
 * @param height
 */
static void bufferBitmap(uint8_t row, uint16_t col, const uint8_t *bitmap, 
        uint16_t width, uint16_t height) {
    uint16_t size = width * height / 8;
    uint16_t origin = DISPLAY_WIDTH * DISPLAY_H_BYTES + row - col * DISPLAY_H_BYTES;
    
    // rotate each 8 x 8 pixel 90° clockwise and flip horizontally
    uint8_t rotated[8];
    memset(rotated, 0, 8);
    uint16_t n = 0, w = 0;
    uint16_t address = origin;
    for (uint16_t i = 0; i < size; i++) {
        uint8_t next = pgm_read_byte(&bitmap[n]);
        // read bytes column by column
        n += width / 8;
        if ((i + 1) % width == 0 && width > 8) {
            n = i / width + 1;
        }
        
        // rotate 8 x 8 pixel
        uint16_t m = i / 8 * 8;
        for (uint8_t r = 0; r < 8; r++) {
            uint8_t bit = (next & (1 << (7 - r))) ? 1 : 0;
            rotated[r] |= bit << (7 - i + m);
        }

        // buffer 8 x 8 rotated pixel
        if ((i + 1) % 8 == 0) {
            for (uint8_t r = 0; r < 8; r++) {
                bufferByte(w, &address, height, rotated[r]);
                w++;
            }
            memset(rotated, 0, 8);
        }
    }
}

/**
 * Writes the bitmap with the given index to the given row and column.
 * @param row
 * @param col
 * @param index
 */
static void writeBitmap(uint8_t row, uint16_t col, uint16_t index) {
    Bitmap bitmap = getBitmap(index);
    
    bufferBitmap(row, col, bitmap.bitmap, bitmap.width, bitmap.height);
}

/**
 * Writes the character with the given pseudo UTF-8 code point to the given
 * row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param code
 */
static void writeChar(uint8_t row, uint16_t col, uint16_t code) {
    Character character = getCharacter(code);
    
    bufferBitmap(row, col, character.bitmap, FONT_WIDTH, FONT_HEIGHT);
}

/**
 * Writes the given string to the given row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param string
 */
static void writeString(uint8_t row, uint16_t col, char *string) {
    uint8_t offset = 0;
    for (; *string != '\0'; string++) {
        uint8_t c = (uint8_t) * string;
        if (c == 194) {
            // multibyte
        } else if (c == 195) {
            // multibyte, add 64 to get code point
            offset = 64;
        } else {
            uint16_t code = c + offset;
            writeChar(row, col, code);
            col += FONT_WIDTH;
            offset = 0;
        }
    }
}

/**
 * Displays a demo for the awesome Unifont.
 */
static void unifontDemo(void) {
    for (uint8_t i = 0; i < DEMO_TEXT_SIZE; i++) {
        writeString(i * 2,  0, getDemoText(i));
    }
}

int main(void) {

    // enable USART RX complete interrupt 0
    // UCSR0B |= (1 << RXCIE0);
    initUSART();
    initPins();
    initSPI();
    initTimer();

    // enable global interrupts
    sei();

    while (true) {

        if (!once) {
            sramFun();
            setFrame(0x00);
            writeBitmap(1, 194, TUX);
            unifontDemo();

            ledOn();
            initDisplay();
            resetAddressCounter();
            sramToDisplay();
            updateDisplay();
            ledOff();

            once = true;
        }

        // display should not be updated more frequently than once every 180 seconds
        if (ints >= INTS_SEC * 180) {
            ints = 0;
            // do something and update the display
        }
    }

    return 0;
}
