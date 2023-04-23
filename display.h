/* 
 * File:   display.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:56
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "dejavu.h"

/**
 * Copies image data from SRAM to display.
 */
void sramToDisplay(void);

/**
 * Fills the frame (SRAM) with the given byte, i.e. 0x00 for all white
 * and 0xff for all black.
 * @param byte
 */
void setFrame(uint8_t byte);

/**
 * Writes the bitmap with the given index to the given row and column.
 * @param row
 * @param col
 * @param index
 */
void writeBitmap(uint16_t row, uint16_t col, uint16_t index);

/**
 * Writes the character with the given pseudo UTF-8 code point to the given
 * row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param code
 */
void writeChar(uint16_t row, uint16_t col, DCharacter character);

/**
 * Writes the given string to the given row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param string
 */
void writeString(uint16_t row, uint16_t col, char *string);

/**
 * Displays a demo for the awesome Unifont.
 */
void unifontDemo(void);

/**
 * Initializes the display, resets the address counter,
 * copys image data from SRAM to display and updates it.
 */
void display(void);

#endif /* DISPLAY_H */
