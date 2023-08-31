/* 
 * File:   font.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 25. April 2023, 21:00
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "font.h"

Glyph getGlyph(Font font, uint16_t code) {
    
    // https://en.wikipedia.org/wiki/Binary_search_algorithm
    uint8_t l = 0;
    uint8_t r = font.length - 1;
    
    while (r != l) {
        uint8_t m = ((l + r) / 2) + 1;
        if (pgm_read_word(&font.glyphs[m].code) > code) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    
    if (pgm_read_word(&font.glyphs[l].code) == code) {
        // found code point, get and return glyph
        static Glyph glyph;
        memcpy_P(&glyph, &font.glyphs[l], sizeof (Glyph));

        return glyph;
    }
    
    // return question mark if unknown code point
    return getGlyph(font, 0x003f);
}