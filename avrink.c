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
 * TODO writing to the display while reading from SRAM in sequential mode would
 * be much more efficient but does not allow to rotate - so this is for later
 */
static void sramToDisplay(void) {
    uint16_t heightInBytes = getHeightInBytes();
    uint16_t bytes = DISPLAY_WIDTH * heightInBytes;

    // rotate origin from upper right to upper left and write bytes row by row
    uint16_t address = 0;
    uint16_t column = DISPLAY_WIDTH;
    for (uint16_t i = 0; i < bytes; i++) {
        if (i % heightInBytes == 0) {
            column--;
            address = column;
        }
        uint8_t byte = sramRead(address);
        imageWrite(~byte);
        address += DISPLAY_WIDTH;
    }

    printString("done copying from SRAM to display\r\n");
}

/**
 * Writes the character with the given pseudo UTF-8 code point to the given
 * row and column and rotates it 90° clockwise.
 * @param row (8 pixels)
 * @param column (1 pixel)
 * @param code
 */
static void writeChar(uint8_t row, uint16_t column, uint16_t code) {
    uint16_t origin = row * DISPLAY_WIDTH + column;
    const uint8_t *bytes = getBitmap(code);
    
    uint8_t rotated[FONT_SIZE];
    memset(rotated, 0, sizeof (rotated));
    for (uint8_t i = 0; i < FONT_SIZE; i++) {
        uint8_t byte = pgm_read_byte(&bytes[i]);
        uint8_t j = i / 8 * 8;
        for (uint8_t r = 0; r < 8; r++) {
            uint8_t bit = (byte & (1 << (7 - r))) ? 1 : 0;
            rotated[r + j] |= bit << (7 - i + j);
        }
    }
    
    for (uint8_t i = 0; i < FONT_SIZE; i++) {
        if (i == FONT_WIDTH) {
            // next line
            origin += DISPLAY_WIDTH - FONT_WIDTH;
        }
        uint16_t address = origin + i;
        sramWrite(address, rotated[i]);
    }
}

/**
 * Writes the given string to the given row and column.
 * @param row (8 pixels)
 * @param column (1 pixel)
 * @param string
 */
static void writeString(uint8_t row, uint16_t column, char *string) {
    uint8_t offset = 0;
    for (; *string != '\0'; string++) {
        uint8_t c = (uint8_t)*string;
        if (c == 194) {
            // multibyte
        } else if (c == 195) {
            // multibyte, add 64 to get code point
            offset = 64;
        } else {
            uint16_t code = c + offset;
            writeChar(row, column, code);
            column += FONT_WIDTH;
            offset = 0;
        }
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

            // prepare image in SRAM
            // blank the image
            uint16_t bytes = DISPLAY_WIDTH * getHeightInBytes();
            for (int i = 0; i < bytes; i++) {
                sramWrite(i, 0);
            }

            writeString( 0, 0, "Hello GNU Unifont! \a");
            writeString( 2, 0, "!\"#$%&'()*+,-./0123456789");
            writeString( 4, 0, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
            writeString( 6, 0, ":;<=>?@[\\]^_`{|}~");
            writeString( 8, 0, "abcdefghijklmnopqrstuvwxyz");
            writeString(10, 0, "äöü");

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
