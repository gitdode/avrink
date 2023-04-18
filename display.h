/* 
 * File:   display.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:56
 */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * Copy image data from SRAM to display.
 * TODO write to display while reading from SRAM in sequential mode
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
void writeBitmap(uint8_t row, uint16_t col, uint16_t index);

/**
 * Writes the character with the given pseudo UTF-8 code point to the given
 * row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param code
 */
void writeChar(uint8_t row, uint16_t col, uint16_t code);

/**
 * Writes the given string to the given row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param string
 */
void writeString(uint8_t row, uint16_t col, char *string);

/**
 * Displays a demo for the awesome Unifont.
 */
void unifontDemo(void);

#endif /* DISPLAY_H */

