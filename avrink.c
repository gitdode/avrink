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
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define DDR_LED   DDRC
#define PORT_LED  PORTC
#define PIN_LED   PC5

#define DDR_SPI   DDRB
#define PORT_SPI  PORTB
#define PIN_SS    PB2
#define PIN_MOSI  PB3
#define PIN_MISO  PB4
#define PIN_SCK   PB5

#define DDR_DISP  DDRD
#define PORT_DISP PORTD
#define PINP_DISP PIND
#define PIN_ECS   PD5 // display chip select
#define PIN_DC    PD6 // display data/command
#define PIN_RST   PD7 // display reset
#define PIN_BUSY  PD4 // display busy

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

    // set display ECS, D/C and RESET pin as output pin
    DDR_DISP |= (1 << PIN_ECS);
    DDR_DISP |= (1 << PIN_DC);
    DDR_DISP |= (1 << PIN_RST);
    // enable pullup on all output pins
    PORT_DISP |= (1 << PIN_ECS);
    PORT_DISP |= (1 << PIN_DC);
    PORT_DISP |= (1 << PIN_RST);
    // set display BUSY pin as input pin
    DDR_DISP &= ~(1 << PIN_BUSY);
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

static void spiTransmit(char data) {
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);
}

static void display(void) {
    PORT_LED |= (1 << PIN_LED);
    
    spiTransmit('D');
    
    // something like that?
    // set CS low to send command/data
    // PORT_DISP &= ~(1 << PIN_ECS);
    // set D/C low to send command
    // PORT_DISP &= ~(1 << PIN_DC);
    // set D/C high to send data
    // PORT_DISP |= (1 << PIN_DC);
    // set CS high after after sending command/data
    // PORT_DISP |= (1 << PIN_ECS);

    // 1. Power On
    // VCI already supplied - could supply by MCU output pin?
    // - Supply VCI
    // - Wait 10ms
    _delay_ms(10);

    // 2. Set Initial Configuration
    // board selects 4-wire SPI by pulling BS1 low?
    // - Define SPI interface to communicate with MCU
    // - HW Reset
    // - SW Reset by Command 0x12
    // - Wait 10ms
    _delay_ms(10);

    // 3. Send Initialization Code
    // - Set gate driver output by Command 0x01
    // - Set display RAM size by Command 0x11, 0x44, 0x45
    // - Set panel border by Command 0x3C

    // 4. Load Waveform LUT
    // - Sense temperature by int/ext TS by Command 0x18
    // - Load waveform LUT from OTP by Command 0x22, 0x20 or by MCU
    // - Wait BUSY Low
    loop_until_bit_is_clear(PINP_DISP, PIN_BUSY);

    // 5. Write Image and Drive Display Panel
    // - Write image data in RAM by Command 0x4E, 0x4F, 0x24, 0x26
    // - Set softstart setting by Command 0x0C
    // - Drive display panel by Command 0x22, 0x20
    // - Wait BUSY Low
    loop_until_bit_is_clear(PINP_DISP, PIN_BUSY);

    // should do this only when VCI is supplied by MCU pin?
    // 6. Power Off
    // - Deep sleep by Command 0x10
    // - Power OFF

    PORT_LED &= ~(1 << PIN_LED);
}

int main(void) {

    initPins();
    initSPI();
    initTimer();

    // enable global interrupts
    sei();

    while (true) {

        if (!once) {
            display();
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
