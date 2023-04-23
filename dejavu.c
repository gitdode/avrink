/* 
 * File:   dejavu.c
 * Author: torsten.roemer@luniks.net
 * https://dejavu-fonts.github.io/License.html
 *
 * Created on 23. April 2023, 18:41
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "dejavu.h"
#include "utils.h"

static const uint8_t EXCLAMATION_MARK[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0,
0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t NUMBER_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xf0, 0x00, 0x03, 0xc0, 0xe0,
0x00, 0x03, 0xc1, 0xe0, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x07, 0x81, 0xe0, 0x00, 0x07, 0x81, 0xc0,
0x00, 0x07, 0x83, 0xc0, 0x00, 0x0f, 0x03, 0xc0, 0x00, 0x0f, 0x03, 0xc0, 0x00, 0x0f, 0x03, 0x80,
0x07, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe,
0x00, 0x1e, 0x0f, 0x00, 0x00, 0x1c, 0x0f, 0x00, 0x00, 0x3c, 0x0f, 0x00, 0x00, 0x3c, 0x0e, 0x00,
0x00, 0x3c, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x3f, 0xff, 0xff, 0xf0,
0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xf0, 0x00, 0xf0, 0x38, 0x00,
0x00, 0xf0, 0x78, 0x00, 0x01, 0xe0, 0x78, 0x00, 0x01, 0xe0, 0x78, 0x00, 0x01, 0xe0, 0x70, 0x00,
0x01, 0xe0, 0xf0, 0x00, 0x03, 0xc0, 0xf0, 0x00, 0x03, 0xc0, 0xf0, 0x00, 0x03, 0xc0, 0xe0, 0x00,
0x03, 0xc1, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t ASTERISK[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00,
0x00, 0x01, 0xc0, 0x00, 0x01, 0x01, 0xc0, 0x40, 0x03, 0xc1, 0xc1, 0xe0, 0x03, 0xe1, 0xc3, 0xe0,
0x00, 0xf9, 0xcf, 0x80, 0x00, 0x3d, 0xde, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x07, 0xf0, 0x00,
0x00, 0x07, 0xf0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x3d, 0xde, 0x00, 0x00, 0xf9, 0xcf, 0x80,
0x03, 0xe1, 0xc3, 0xe0, 0x03, 0xc1, 0xc1, 0xe0, 0x01, 0x01, 0xc0, 0x40, 0x00, 0x01, 0xc0, 0x00,
0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t PLUS_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t COMMA[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xc0, 0x0f, 0xc0, 0x0f, 0x80, 0x0f, 0x80,
0x0f, 0x80, 0x0f, 0x00, 0x1f, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t HYPHEN_MINUS[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x3f, 0xfc,
0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t FULL_STOP[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t SOLIDUS[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x80,
0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x1e, 0x00,
0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3c, 0x00,
0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00,
0x00, 0x3c, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00,
0x00, 0xf0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00,
0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_0[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x3f, 0xfe, 0x00,
0x00, 0x7f, 0xff, 0x00, 0x00, 0xfc, 0x1f, 0x80, 0x01, 0xf0, 0x07, 0xc0, 0x01, 0xf0, 0x07, 0xc0,
0x01, 0xe0, 0x03, 0xc0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0,
0x03, 0xc0, 0x01, 0xe0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0,
0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0,
0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0,
0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0,
0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xf0, 0x07, 0xc0,
0x01, 0xf0, 0x07, 0xc0, 0x00, 0xfc, 0x1f, 0x80, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x3f, 0xfe, 0x00,
0x00, 0x1f, 0xfc, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_1[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00,
0x00, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0xfc, 0xf0, 0x00, 0x00, 0xc0, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x00, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0xe0,
0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_2[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x01, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0x80,
0x03, 0xff, 0xff, 0xc0, 0x03, 0xf8, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0xf0, 0x02, 0x00, 0x00, 0xf0,
0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78,
0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf0,
0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0xc0,
0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0x00,
0x00, 0x01, 0xf8, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0xc0, 0x00,
0x00, 0x1f, 0x80, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00,
0x01, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xf8,
0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_3[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xff, 0x00,
0x03, 0xff, 0xff, 0x80, 0x03, 0xe0, 0x1f, 0xc0, 0x02, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xe0,
0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0,
0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x1f, 0x80,
0x00, 0x1f, 0xff, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x00,
0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xe0,
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0,
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x04, 0x00, 0x03, 0xe0,
0x07, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x1f, 0xc0, 0x07, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0x00,
0x03, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_4[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x7e, 0x00,
0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x01, 0xde, 0x00, 0x00, 0x03, 0xde, 0x00,
0x00, 0x03, 0x9e, 0x00, 0x00, 0x07, 0x9e, 0x00, 0x00, 0x0f, 0x1e, 0x00, 0x00, 0x0f, 0x1e, 0x00,
0x00, 0x1e, 0x1e, 0x00, 0x00, 0x1c, 0x1e, 0x00, 0x00, 0x3c, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00,
0x00, 0x78, 0x1e, 0x00, 0x00, 0xf0, 0x1e, 0x00, 0x00, 0xf0, 0x1e, 0x00, 0x01, 0xe0, 0x1e, 0x00,
0x03, 0xc0, 0x1e, 0x00, 0x03, 0xc0, 0x1e, 0x00, 0x07, 0x80, 0x1e, 0x00, 0x07, 0x80, 0x1e, 0x00,
0x0f, 0x00, 0x1e, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0,
0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00,
0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00,
0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_5[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xc0,
0x01, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xc0, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00,
0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00,
0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xef, 0xf0, 0x00, 0x01, 0xff, 0xfc, 0x00,
0x01, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0x80, 0x01, 0xe0, 0x1f, 0xc0, 0x01, 0x00, 0x07, 0xc0,
0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0xf0,
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0,
0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x01, 0xe0, 0x04, 0x00, 0x03, 0xe0,
0x07, 0x00, 0x07, 0xc0, 0x07, 0xe0, 0x1f, 0xc0, 0x07, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0x00,
0x03, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_6[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x80,
0x00, 0x7f, 0xff, 0x80, 0x00, 0x7e, 0x01, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00,
0x01, 0xe0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00,
0x03, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x83, 0xf8, 0x00, 0x07, 0x8f, 0xfe, 0x00,
0x07, 0x9f, 0xff, 0x00, 0x07, 0xbf, 0xff, 0x80, 0x07, 0xfc, 0x0f, 0xc0, 0x07, 0xf8, 0x03, 0xe0,
0x07, 0xf0, 0x01, 0xe0, 0x07, 0xe0, 0x01, 0xe0, 0x07, 0xe0, 0x00, 0xf0, 0x07, 0xc0, 0x00, 0xf0,
0x07, 0xc0, 0x00, 0xf0, 0x07, 0xc0, 0x00, 0xf0, 0x07, 0xc0, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0xf0,
0x03, 0xc0, 0x00, 0xf0, 0x03, 0xe0, 0x00, 0xf0, 0x03, 0xe0, 0x01, 0xe0, 0x01, 0xf0, 0x01, 0xe0,
0x01, 0xf8, 0x03, 0xe0, 0x00, 0xfc, 0x0f, 0xc0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00,
0x00, 0x1f, 0xfe, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_7[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xf0,
0x07, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xe0,
0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80,
0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1e, 0x00,
0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x7c, 0x00,
0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00,
0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0x80, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00,
0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_8[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0x00,
0x00, 0xff, 0xff, 0x80, 0x01, 0xf8, 0x0f, 0xc0, 0x01, 0xf0, 0x07, 0xc0, 0x03, 0xe0, 0x03, 0xe0,
0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0,
0x03, 0xc0, 0x01, 0xe0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xf0, 0x07, 0xc0, 0x00, 0xf8, 0x0f, 0x80,
0x00, 0x7f, 0xff, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x80,
0x01, 0xf8, 0x0f, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x03, 0xc0, 0x01, 0xe0, 0x03, 0xc0, 0x01, 0xe0,
0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0,
0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x07, 0xc0, 0x01, 0xf0, 0x03, 0xc0, 0x01, 0xe0,
0x03, 0xe0, 0x03, 0xe0, 0x01, 0xf8, 0x0f, 0xc0, 0x01, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0x80,
0x00, 0x3f, 0xfe, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DIGIT_9[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x7f, 0xfe, 0x00,
0x00, 0xff, 0xff, 0x00, 0x01, 0xf8, 0x1f, 0x80, 0x03, 0xe0, 0x0f, 0xc0, 0x03, 0xc0, 0x07, 0xc0,
0x03, 0xc0, 0x03, 0xe0, 0x07, 0x80, 0x03, 0xe0, 0x07, 0x80, 0x01, 0xe0, 0x07, 0x80, 0x01, 0xe0,
0x07, 0x80, 0x01, 0xf0, 0x07, 0x80, 0x01, 0xf0, 0x07, 0x80, 0x01, 0xf0, 0x07, 0x80, 0x01, 0xf0,
0x07, 0x80, 0x03, 0xf0, 0x03, 0xc0, 0x03, 0xf0, 0x03, 0xc0, 0x07, 0xf0, 0x03, 0xe0, 0x0f, 0xf0,
0x01, 0xf8, 0x1f, 0xf0, 0x00, 0xff, 0xfe, 0xf0, 0x00, 0x7f, 0xfc, 0xf0, 0x00, 0x3f, 0xf8, 0xf0,
0x00, 0x0f, 0xe0, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xe0,
0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0,
0x00, 0x00, 0x0f, 0x80, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xfe, 0x00,
0x00, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t COLON[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t SEMICOLON[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0,
0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xc0, 0x0f, 0xc0, 0x0f, 0x80, 0x0f, 0x80,
0x0f, 0x80, 0x0f, 0x00, 0x1f, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t LESS_THAN_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x78,
0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x01, 0xff, 0x80,
0x00, 0x0f, 0xfe, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x01, 0xff, 0x80, 0x00, 0x0f, 0xfc, 0x00, 0x00,
0x0f, 0xf0, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00,
0x01, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0x80,
0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x78,
0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t EQUALS_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8,
0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf8,
0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t GREATER_THAN_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
0x0f, 0xe0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00,
0x00, 0x3f, 0xf8, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xf8,
0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x1f, 0xf8,
0x00, 0x00, 0xff, 0xc0, 0x00, 0x07, 0xff, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0xff, 0xc0, 0x00,
0x07, 0xff, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t QUESTION_MARK[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0xff, 0xff, 0x00,
0x01, 0xff, 0xff, 0x00, 0x01, 0xf8, 0x1f, 0x80, 0x01, 0xc0, 0x07, 0xc0, 0x01, 0x00, 0x03, 0xc0,
0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0,
0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x3f, 0x00,
0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x03, 0xe0, 0x00,
0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00,
0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00,
0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00,
0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t COMMERCIAL_AT[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x7f, 0x03, 0xe0,
0x00, 0xfc, 0x00, 0xf0, 0x01, 0xf0, 0x00, 0x78, 0x01, 0xe0, 0x00, 0x38, 0x03, 0xc0, 0x00, 0x3c,
0x07, 0xc0, 0x00, 0x1c, 0x07, 0x80, 0x00, 0x1c, 0x07, 0x80, 0x1f, 0x1c, 0x0f, 0x00, 0x7f, 0xdc,
0x0f, 0x00, 0xff, 0xfc, 0x0f, 0x01, 0xf0, 0xfc, 0x1e, 0x03, 0xe0, 0x7c, 0x1e, 0x03, 0xc0, 0x3c,
0x1e, 0x07, 0xc0, 0x3c, 0x1e, 0x07, 0x80, 0x1c, 0x1e, 0x07, 0x80, 0x1c, 0x1e, 0x07, 0x80, 0x1c,
0x1e, 0x07, 0x80, 0x1c, 0x1e, 0x07, 0x80, 0x1c, 0x1e, 0x07, 0x80, 0x1c, 0x1e, 0x07, 0xc0, 0x3c,
0x1e, 0x03, 0xc0, 0x3c, 0x0f, 0x03, 0xe0, 0x7c, 0x0f, 0x01, 0xf0, 0xfc, 0x0f, 0x00, 0xff, 0xfc,
0x0f, 0x80, 0x7f, 0xdc, 0x07, 0x80, 0x1f, 0x1c, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00,
0x03, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00,
0x00, 0x3f, 0x80, 0x40, 0x00, 0x0f, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t C[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x1f, 0xff, 0xe0,
0x00, 0x3f, 0xff, 0xe0, 0x00, 0x7e, 0x03, 0xe0, 0x00, 0xf8, 0x00, 0x60, 0x00, 0xf0, 0x00, 0x20,
0x01, 0xf0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00,
0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00,
0x07, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00,
0x03, 0xc0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x20,
0x00, 0xf8, 0x00, 0x60, 0x00, 0x7e, 0x03, 0xe0, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xe0,
0x00, 0x07, 0xff, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t DEGREE_SIGN[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x07, 0xc0, 0x1f, 0xf0, 0x3f, 0xf8, 0x78, 0x3c, 0x70, 0x1c, 0xe0, 0x0e, 0xe0, 0x0e,
0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0x70, 0x1c, 0x78, 0x3c, 0x3f, 0xf8, 0x1f, 0xf0, 0x07, 0xc0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const DCharacter chars[] PROGMEM = {
    {0x0021, 16, EXCLAMATION_MARK},
    {0x0023, 32, NUMBER_SIGN},
    {0x002a, 32, ASTERISK},
    {0x002b, 32, PLUS_SIGN},
    {0x002c, 16, COMMA},
    {0x002d, 16, HYPHEN_MINUS},
    {0x002e, 16, FULL_STOP},
    {0x002f, 32, SOLIDUS},
    {0x0030, 32, DIGIT_0},
    {0x0031, 32, DIGIT_1},
    {0x0032, 32, DIGIT_2},
    {0x0033, 32, DIGIT_3},
    {0x0034, 32, DIGIT_4},
    {0x0035, 32, DIGIT_5},
    {0x0036, 32, DIGIT_6},
    {0x0037, 32, DIGIT_7},
    {0x0038, 32, DIGIT_8},
    {0x0039, 32, DIGIT_9},
    {0x003a, 16, COLON},
    {0x003b, 16, SEMICOLON},
    {0x003c, 32, LESS_THAN_SIGN},
    {0x003d, 32, EQUALS_SIGN},
    {0x003e, 32, GREATER_THAN_SIGN},
    {0x003f, 32, QUESTION_MARK},
    {0x0040, 32, COMMERCIAL_AT},
    {0x0043, 32, C},
    {0x00b0, 16, DEGREE_SIGN}
};

DCharacter getDCharacter(uint16_t code) {
    size_t length = ARRAY_LENGTH(chars);
    for (size_t i = 0; i < length; i++) {
        if (pgm_read_word(&chars[i].code) == code) {
            static DCharacter character;
            memcpy_P(&character, &chars[i], sizeof (DCharacter));
            
            return character;
        }
    }
    
    // return question mark if unknown code point
    return getDCharacter(0x003f);
}