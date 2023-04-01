/* 
 * File:   sram.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pins.h"
#include "sram.h"
#include "spi.h"

#include "usart.h"

/**
 * Selects the SRAM to talk to via SPI.
 */
static void csLow(void) {
    PORT_SRDI &= ~(1 << PIN_SRCS);
}

/**
 * Delects the SRAM to talk to via SPI.
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

// TODO read until null byte instead of given length?
char * sramReadString(uint16_t startAddress, size_t length) {
    char *read = (char *)malloc(length + 1);
    for (size_t i = 0; i < length; i++) {
        uint16_t address = startAddress + i;
        read[i] = sramRead(address);
        if (address == SRAM_HIGH) {
            break;
        }
    }
    read[length] = '\0';
    
    return read;
}

uint8_t sramReadStatus(void) {
    csLow();
    transmit(SRAM_RDSR);
    uint8_t status = transmit(0);
    csHigh();

    return status;
}