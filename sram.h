/* 
 * File:   sram.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#ifndef SRAM_H
#define SRAM_H

#define SRAM_READ   0x3
#define SRAM_WRITE  0x2
#define SRAM_RDSR   0x5
#define SRAM_WRSR   0x1

#define MODE_SEQU   6
#define MODE_PAGE   7

#define SRAM_HIGH   0x1fff

/**
 * Writes the given byte to the given address.
 * @param address
 * @param data
 */
void sramWrite(uint16_t address, uint8_t data);

/**
 * Writes the given string starting at the given address, never beyond
 * the highest memory address, and returns the number of bytes actually
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
 * Reads length - 1 bytes starting at the given address, never beyond 
 * the highest memory address, into the given buffer and adds a trailing 
 * null terminator.
 * @param startAddress
 * @param string
 * @param length
 */
void sramReadString(uint16_t startAddress, char *string, size_t length);

/**
 * Writes the given status.
 * @param status
 */
void sramWriteStatus(uint8_t status);

/**
 * Reads the status and returns it.
 * @return 
 */
uint8_t sramReadStatus(void);

#endif /* SRAM_H */

