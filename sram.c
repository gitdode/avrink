/* 
 * File:   sram.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sram.h"
#include "pins.h"
#include "spi.h"

#include "usart.h"

/**
 * Selects the SRAM to talk to via SPI.
 */
static void csLow(void) {
    PORT_SRDI &= ~(1 << PIN_SRCS);
}

/**
 * Deselects the SRAM to talk to via SPI.
 */
static void csHigh(void) {
    PORT_SRDI |= (1 << PIN_SRCS);
}

void sramWrite(uint16_t address, uint8_t data) {
    csLow();
    transmit(SRAM_WRITE);
    transmit(address >> 8);
    transmit(address);
    transmit(data);
    csHigh();
}

size_t sramWriteString(uint16_t startAddress, char *data) {
    size_t length = strlen(data);
    size_t written = 0;
    for (size_t i = 0; i < length; i++) {
        uint16_t address = startAddress + i;
        char c = *data++;
        sramWrite(address, c);
        written++;
        if (address == SRAM_HIGH) {
            break;
        }
    }

    return written;
}

uint8_t sramRead(uint16_t address) {
    csLow();
    transmit(SRAM_READ);
    transmit(address >> 8);
    transmit(address);
    uint8_t read = transmit(0);
    csHigh();

    return read;
}

void sramReadString(uint16_t startAddress, char *buf, size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        uint16_t address = startAddress + i;
        buf[i] = sramRead(address);
        if (address == SRAM_HIGH) {
            break;
        }
    }
    buf[length - 1] = '\0';
}

uint8_t sramReadStatus(void) {
    csLow();
    transmit(SRAM_RDSR);
    uint8_t status = transmit(0);
    csHigh();

    return status;
}
