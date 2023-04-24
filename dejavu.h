/* 
 * File:   dejavu.h
 * Author: torsten.roemer@luniks.net
 * https://dejavu-fonts.github.io/License.html
 *
 * Created on 23. April 2023, 18:41
 */

#ifndef DEJAVU_H
#define DEJAVU_H

#include "font.h"

#define DEJAVU_WIDTH 32
#define DEJAVU_HEIGHT 56
#define DEJAVU_SIZE DEJAVU_WIDTH * DEJAVU_HEIGHT / 8

/**
 * Returns the glyph at the given pseudo UTF-8 code point, i.e. 0x00f6 
 * for U+00F6. If there is no glyph for that code point, a question mark 
 * is returned.
 * @param code
 * @return Glyph
 */
Glyph getDejaVuGlyph(uint16_t code);

#endif /* DEJAVU_H */

