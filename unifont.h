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
#define UNIFONT_DEMO_LINE_SIZE 64

/**
 * Demo text lines.
 */
extern const __flash char* demoTextLines[UNIFONT_DEMO_SIZE];

/**
 * Unifont font.
 */
extern const __flash Font unifontFont;

#endif /* UNIFONT_H */

