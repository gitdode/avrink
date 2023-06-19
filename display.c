/* 
 * File:   display.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:56
 */

#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "unifont.h"
#include "dejavu.h"
#include "bitmaps.h"
#include "sram.h"
#include "eink.h"
#include "usart.h"
#include "utils.h"

/**
 * Writes the given byte at the given index for the given bitmap height
 * to its address/location. 
 * @param index
 * @param address
 * @param height
 * @param byte
 */
static void bufferByte(uint16_t index, uint16_t *address, uint16_t height,
        uint8_t byte) {
    if (index % height == 0) {
        if (index > 0) {
            *address -= height / 8 - 1;
        }
    } else if (index % 8 == 0) {
        *address += 8 * DISPLAY_H_BYTES + 1;
    }

    sramWrite(*address, byte);
    *address -= DISPLAY_H_BYTES;
}

/**
 * Writes the given bitmap stored in program memory with the given width  
 * and height to the given row and column to SRAM. Width and height must be 
 * multiples of 8.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param bitmap
 * @param width
 * @param height
 */
static void bufferBitmap(uint8_t row, uint16_t col, const uint8_t *bitmap,
        uint16_t width, uint16_t height) {
    uint16_t size = width * height / 8;
    uint16_t origin = DISPLAY_WIDTH * DISPLAY_H_BYTES + row - col * DISPLAY_H_BYTES;

    // rotate each 8 x 8 pixel 90° clockwise and flip horizontally
    uint8_t rotated[8];
    memset(rotated, 0, 8);
    uint16_t n = 0, w = 0;
    for (uint16_t i = 0; i < size; i++) {
        uint8_t next = pgm_read_byte(&bitmap[n]);
        // read bytes column by column
        n += width / 8;
        if ((i + 1) % height == 0) {
            n = i / height + 1;
        }

        // rotate 8 x 8 pixel
        uint16_t m = i / 8 * 8;
        for (uint8_t r = 0; r < 8; r++) {
            uint8_t bit = (next & (1 << (7 - r))) ? 1 : 0;
            rotated[r] |= bit << (7 - i + m);
        }

        // buffer 8 x 8 rotated pixel
        if ((i + 1) % 8 == 0) {
            for (uint8_t r = 0; r < 8; r++) {
                bufferByte(w, &origin, height, rotated[r]);
                w++;
            }
            memset(rotated, 0, 8);
        }
    }
}

// TODO write to display while reading from SRAM in sequential mode
void sramToDisplay(void) {
    uint16_t bytes = DISPLAY_WIDTH * DISPLAY_H_BYTES;

    for (uint16_t i = 0; i < bytes; i++) {
        uint8_t byte = sramRead(i);
        // remove negation for dark mode :)
        imageWrite(~byte);
    }

    printString("done copying from SRAM to display\r\n");
}

void setFrame(uint8_t byte) {
    uint16_t bytes = DISPLAY_WIDTH * DISPLAY_H_BYTES;

    for (int i = 0; i < bytes; i++) {
        sramWrite(i, byte);
    }
}

uint8_t writeBitmap(uint16_t row, uint16_t col, uint16_t index) {
    Bitmap bitmap = getBitmap(index);
    bufferBitmap(row, col, bitmap.bitmap, bitmap.width, bitmap.height);
    
    return bitmap.width;
}

uint8_t writeGlyph(uint16_t row, uint16_t col, Font font, uint16_t code) {
    Glyph glyph = getGlyph(font, code);
    bufferBitmap(row, col, glyph.bitmap, glyph.width, font.height);
    
    return glyph.width;
}

void writeString(uint16_t row, uint16_t col, Font font, char *string) {
    uint8_t offset = 0;
    for (; *string != '\0'; string++) {
        uint8_t c = (uint8_t) *string;
        if (c == 194) {
            // multibyte
        } else if (c == 195) {
            // multibyte, add 64 to get code point
            offset = 64;
        } else {
            uint16_t code = c + offset;
            col += writeGlyph(row, col, font, code);
            offset = 0;
        }
    }
}

void unifontDemo(void) {
    Font unifont = getUnifont();
    for (uint8_t i = 0; i < UNIFONT_DEMO_SIZE; i++) {
        writeString(i * 2, 0, unifont, getUnifontDemo(i));
    }
}

void display(void) {
    initDisplay();
    resetAddressCounter();
    sramToDisplay();
    updateDisplay();
}
