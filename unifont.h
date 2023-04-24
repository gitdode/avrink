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
 * Returns the given line of demo text.
 * @param line
 * @return address
 */
char * getDemoText(uint8_t line);

/**
 * Returns the glyph at the given pseudo UTF-8 code point, i.e. 0x00f6 
 * for U+00F6. If there is no glyph for that code point, a question mark 
 * is returned.
 * @param code
 * @return Glyph
 */
Glyph getUnifontGlyph(uint16_t code);

#endif /* UNIFONT_H */

