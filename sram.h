/* 
 * File:   sram.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#ifndef SRAM_H
#define SRAM_H

#define SRAM_READ  0x3
#define SRAM_WRITE 0x2
#define SRAM_RDSR  0x5
#define SRAM_WRSR  0x1

#define SRAM_HIGH  0x1fff

/**
 * Writes the given byte to the given address.
 * @param address
 * @param data
 */
void sramWrite(uint16_t address, uint8_t data);

/**
 * Writes the given string starting at the given address but never beyond
 * the highest memory address 0x1fff, and returns the number of bytes actually
 * written.
 * @param startAddress
 * @param data
 * @return number of bytes written
 */
size_t sramWriteString(uint16_t startAddress, char *data);

/**
 * Reads the byte at the given address and returns it.
 * @param address
 * @return byte
 */
uint8_t sramRead(uint16_t address);

/**
 * Reads a string with the given length starting at the given address
 * and returns it.
 * @param startAddress
 * @param length
 * @return string
 */
char * sramReadString(uint16_t startAddress, size_t length);

uint8_t sramReadStatus(void);

#endif /* SRAM_H */

