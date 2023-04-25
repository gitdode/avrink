/* 
 * File:   unifont.h
 * Author: torsten.roemer@luniks.net
 * Unifont is part of the GNU Project: http://savannah.gnu.org/projects/unifont/
 *
 * Created on 8. April 2023, 16:50
 */

#ifndef UNIFONT_H
#define UNIFONT_H

#include "font.h"

#define UNIFONT_WIDTH 8
#define UNIFONT_HEIGHT 16
#define UNIFONT_SIZE UNIFONT_WIDTH * UNIFONT_HEIGHT / 8

#define DEMO_TEXT_SIZE 7

/**
 * Glyphs of this font.
 */
extern const Glyph unifontGlyphs[];

/**
 * Number of glyphs of this font.
 */
extern const uint8_t unifontLength;

/**
 * Returns the given line of demo text.
 * @param line
 * @return address
 */
char * getDemoText(uint8_t line);

#endif /* UNIFONT_H */

