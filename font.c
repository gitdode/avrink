/* 
 * File:   font.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 25. April 2023, 21:00
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "font.h"

Glyph getGlyph(uint16_t code, const Glyph *glyphs, const size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (pgm_read_word(&glyphs[i].code) == code) {
            static Glyph glyph;
            memcpy_P(&glyph, &glyphs[i], sizeof (Glyph));
            
            return glyph;
        }
    }
    
    // return question mark if unknown code point
    return getGlyph(0x003f, glyphs, length);
}