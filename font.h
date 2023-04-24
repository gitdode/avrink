/* 
 * File:   font.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 24. April 2023, 21:21
 */

#ifndef FONT_H
#define FONT_H

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

#endif /* FONT_H */

