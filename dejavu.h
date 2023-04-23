/* 
 * File:   dejavu.h
 * Author: torsten.roemer@luniks.net
 * https://dejavu-fonts.github.io/License.html
 *
 * Created on 23. April 2023, 18:41
 */

#ifndef DEJAVU_H
#define DEJAVU_H

#define DEJAVU_WIDTH 32
#define DEJAVU_HEIGHT 56
#define DEJAVU_SIZE DEJAVU_WIDTH * DEJAVU_HEIGHT / 8

/**
 * A character with its pseudo UTF-8 code point, width and bitmap.
 */
typedef struct {
    const uint16_t code;
    const uint8_t width;
    const uint8_t *bitmap;
} DCharacter;

/**
 * Returns the Character at the given pseudo UTF-8 code point, i.e. 0x00f6 
 * for U+00F6. If there is no character for that code point, a question mark 
 * is returned.
 * @param code
 * @return Character
 */
DCharacter getDCharacter(uint16_t code);

#endif /* DEJAVU_H */

