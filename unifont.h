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

#define UNIFONT_DEMO_SIZE 7

/**
 * Returns the given line of demo text.
 * @param line
 * @return address
 */
char * getUnifontDemo(uint8_t line);

/**
 * Returns an instance of the Unifont font.
 * @return unifont
 */
const Font getUnifont(void);

#endif /* UNIFONT_H */

