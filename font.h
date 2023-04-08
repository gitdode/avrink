/* 
 * File:   font.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 8. April 2023, 16:50
 */

#ifndef FONT_H
#define FONT_H

#define EMOJI_HAPPY 0x100

/**
 * A character with its pseudo UTF-8 code point, pixmap and width in pixels.
 */
typedef struct {
    uint16_t code;
    PGM_P bytes;
    size_t width;
} Character;

/**
 * Gets the character at the given pseudo UTF-8 code point, i.e. 0x00f6 for 
 * U+00F6. If there is no character for that code point, a happy emoji is 
 * returned, because we think positive.
 * @param code
 * @return character
 */
Character getCharacter(uint16_t code);

#endif /* FONT_H */

