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

#include "emoji.h"

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
    sramReadString(0x123, bunny, sizeof(bunny));
    
    char buf[strlen(bunny) + 3];
    snprintf(buf, sizeof(buf), "%s\r\n", bunny);
    printString(buf);
}

/**
 * Copy image data from SRAM to display.
 */
static void sramToDisplay(void) {
    uint16_t heightInBytes = getHeightInBytes();
    uint16_t bytes = DISPLAY_WIDTH * heightInBytes;
    
    // rotate origin from upper right to upper left and write bytes row by row
    uint16_t address = 0;
    int16_t column = DISPLAY_WIDTH;
    for (uint16_t i = 0; i < bytes; i++) {
        if (i % heightInBytes == 0) {
            column--;
            address = column;
        }
        uint8_t byte = sramRead(address);
        imageWrite(byte);
        address += DISPLAY_WIDTH;
    }
    
    printString("done copying from SRAM to display\r\n");
}

/**
 * Draw a real handcrafted emoji into SRAM.
 */
static void writeEmoji(void) {
    // somewhere near the center of the display
    sramWrite(1600, EMOJI00);
    sramWrite(1601, EMOJI01);
    sramWrite(1602, EMOJI02);
    sramWrite(1603, EMOJI03);
    sramWrite(1604, EMOJI04);
    sramWrite(1605, EMOJI05);
    sramWrite(1606, EMOJI06);
    sramWrite(1607, EMOJI07);
    sramWrite(1608, EMOJI08);
    sramWrite(1609, EMOJI09);
    sramWrite(1610, EMOJI0a);
    sramWrite(1611, EMOJI0b);
    sramWrite(1612, EMOJI0c);
    sramWrite(1613, EMOJI0d);
    sramWrite(1614, EMOJI0e);
    sramWrite(1615, EMOJI0f);
    // jump to next line
    sramWrite(1850, EMOJI10);
    sramWrite(1851, EMOJI11);
    sramWrite(1852, EMOJI12);
    sramWrite(1853, EMOJI13);
    sramWrite(1854, EMOJI14);
    sramWrite(1855, EMOJI15);
    sramWrite(1856, EMOJI16);
    sramWrite(1857, EMOJI17);
    sramWrite(1858, EMOJI18);
    sramWrite(1859, EMOJI19);
    sramWrite(1860, EMOJI1a);
    sramWrite(1861, EMOJI1b);
    sramWrite(1862, EMOJI1c);
    sramWrite(1863, EMOJI1d);
    sramWrite(1864, EMOJI1e);
    sramWrite(1865, EMOJI1f);
    
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
                sramWrite(i, 255);
            }
            // write emoji :)
            writeEmoji();
                        
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
