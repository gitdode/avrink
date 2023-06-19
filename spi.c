/* 
 * File:   spi.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#include <stdio.h>
#include <avr/io.h>
#include "pins.h"
#include "spi.h"

void sramSel(void) {
    PORT_SSPI &= ~(1 << PIN_SRCS);
}

void sramDes(void) {
    PORT_SSPI |= (1 << PIN_SRCS);
}

void displaySel(void) {
    PORT_DSPI &= ~(1 << PIN_ECS);
}

void displayDes(void) {
    PORT_DSPI |= (1 << PIN_ECS);
}

uint8_t transmit(uint8_t data) {
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);

    return SPDR;
}