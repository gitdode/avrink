/* 
 * File:   unifont.h
 * Author: torsten.roemer@luniks.net
 * Unifont is part of the GNU Project: http://savannah.gnu.org/projects/unifont/
 *
 * Created on 8. April 2023, 16:50
 */

#ifndef FONT_H
#define FONT_H

#define FONT_WIDTH 8
#define FONT_HEIGHT 16
#define FONT_SIZE FONT_WIDTH * FONT_HEIGHT / 8

#define DEMO_TEXT_SIZE 7

/**
 * A character with its pseudo UTF-8 code point and bitmap.
 */
typedef struct {
    const uint16_t code;
    const uint8_t *bitmap;
} Character;

/**
 * Returns the given line of demo text.
 * @param line
 * @return address
 */
char * getDemoText(uint8_t line);

/**
 * Returns the bitmap of the character at the given pseudo UTF-8 code point, 
 * i.e. 0x00f6 for U+00F6. If there is no character for that code point, 
 * a question mark is returned.
 * @param code
 * @return bitmap
 */
const uint8_t * getUnifontBitmap(uint16_t code);

#endif /* FONT_H */

