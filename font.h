/* 
 * File:   font.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 24. April 2023, 21:21
 */

#ifndef FONT_H
#define FONT_H

/**
 * Fonts available here.
 */
typedef enum {
    UNIFONT,
    DEJAVU
} Font;

/**
 * A glyph with its pseudo UTF-8 code point, width and bitmap.
 */
typedef struct {
    const uint16_t code;
    const uint8_t width;
    const uint8_t *bitmap;
} Glyph;

/**
 * Returns the glyph at the given pseudo UTF-8 code point, i.e. 0x00f6 
 * for U+00F6 from the given glyphs with the given length.
 * If there is no glyph for that code point, a question mark is returned.
 * @param code
 * @param glyphs
 * @param length
 * @return Glyph
 */
Glyph getGlyph(uint16_t code, const Glyph *glyphs, const size_t length);

#endif /* FONT_H */
