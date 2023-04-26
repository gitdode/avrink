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
 * Glyphs of this font.
 */
extern const Glyph dejaVuGlyphs[];

/**
 * Number of glyphs of this font.
 */
extern const uint8_t dejaVuLength;

#endif /* DEJAVU_H */

