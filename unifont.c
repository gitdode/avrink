/* 
 * File:   unifont.c
 * Author: torsten.roemer@luniks.net
 * Unifont is part of the GNU Project: http://savannah.gnu.org/projects/unifont/
 *
 * Created on 8. April 2023, 20:52
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "unifont.h"

const char SPACE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char EXCLAMATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

const char QUOTATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char NUMBER_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x12, 0x12, 0x12, 0x7E, 
    0x24, 0x24, 0x7E, 0x48, 0x48, 0x48, 0x00, 0x00};

const char DOLLAR_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x3E, 0x49, 0x48, 
    0x38, 0x0E, 0x09, 0x49, 0x3E, 0x08, 0x00, 0x00};

const char PERCENT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x31, 0x4A, 0x4A, 0x34, 
    0x08, 0x08, 0x16, 0x29, 0x29, 0x46, 0x00, 0x00};

const char AMPERSAND[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x22, 0x14, 
    0x18, 0x29, 0x45, 0x42, 0x46, 0x39, 0x00, 0x00};

const char APOSTROPHE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char LEFT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x00};

const char RIGHT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x20, 0x10, 0x10, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x00};

const char ASTERISK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 
    0x2A, 0x1C, 0x2A, 0x49, 0x08, 0x00, 0x00, 0x00};

const char PLUS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 
    0x08, 0x7F, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00};

const char COMMA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10};

const char HYPHEN_MINUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char FULL_STOP[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00};

const char SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 
    0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x00, 0x00};

const char DIGIT_0[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x46, 
    0x4A, 0x52, 0x62, 0x42, 0x24, 0x18, 0x00, 0x00};

const char DIGIT_1[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const char DIGIT_2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x0C, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

const char DIGIT_3[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x1C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char DIGIT_4[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 
    0x44, 0x44, 0x7E, 0x04, 0x04, 0x04, 0x00, 0x00};

const char DIGIT_5[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x02, 0x02, 0x02, 0x42, 0x3C, 0x00, 0x00};

const char DIGIT_6[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x20, 0x40, 0x40, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char DIGIT_7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const char DIGIT_8[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char DIGIT_9[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3E, 0x02, 0x02, 0x02, 0x04, 0x38, 0x00, 0x00};

const char COLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};

const char SEMICOLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10, 0x00};

const char LESS_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00};

const char EQUALS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 
    0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00};

const char GREATER_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00};

const char QUESTION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x04, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

const char COMMERCIAL_AT[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x4A, 0x56, 
    0x52, 0x52, 0x52, 0x4E, 0x20, 0x1E, 0x00, 0x00};

const char A[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const char B[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x00, 0x00};

const char C[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char D[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00};

const char E[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const char F[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const char G[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x4E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char H[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const char I[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const char J[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00, 0x00};

const char K[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 
    0x60, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

const char L[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const char M[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x66, 0x66, 
    0x5A, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const char N[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 
    0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x00, 0x00};

const char O[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char P[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const char Q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x5A, 0x66, 0x3C, 0x03, 0x00};

const char R[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x48, 0x44, 0x44, 0x42, 0x42, 0x00, 0x00};

const char S[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x30, 0x0C, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char T[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const char U[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char V[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 
    0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00, 0x00};

const char W[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x5A, 0x5A, 0x66, 0x66, 0x42, 0x42, 0x00, 0x00};

const char X[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 
    0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x00, 0x00};

const char Y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 
    0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const char Z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

const char LEFT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0E, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00};

const char REVERSE_SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x20, 0x10, 
    0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x00, 0x00};

const char RIGHT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00};

const char CIRCUMFLEX_ACCENT[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char LOW_LINE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00};

const char GRAVE_ACCENT[] PROGMEM = {
    0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char a[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char b[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x00, 0x00};

const char c[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const char d[] PROGMEM = {
    0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char e[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const char f[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};

const char g[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3A, 0x44, 
    0x44, 0x44, 0x38, 0x20, 0x3C, 0x42, 0x42, 0x3C};

const char h[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const char i[] PROGMEM = {
    0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const char j[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x0C, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x48, 0x30};

const char k[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x44, 0x48, 
    0x50, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

const char l[] PROGMEM = {
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const char m[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00};

const char n[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const char o[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char p[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40};

const char q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02};

const char r[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const char s[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x30, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00};

const char t[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x00, 0x00};

const char u[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char v[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x24, 0x24, 0x24, 0x18, 0x18, 0x00, 0x00};

const char w[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00};

const char x[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x24, 0x18, 0x18, 0x24, 0x42, 0x42, 0x00, 0x00};

const char y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

const char z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 
    0x04, 0x08, 0x10, 0x20, 0x40, 0x7E, 0x00, 0x00};

const char LEFT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x08, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x08, 0x10, 0x10, 0x0C};

const char VERTICAL_LINE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

const char RIGHT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x10, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x10, 0x08, 0x08, 0x30};

const char TILDE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x31, 0x49, 0x46, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const char ae[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char oe[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const char ue[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const char HAPPY[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0xA5, 
    0x81, 0xA5, 0x99, 0x42, 0x3C, 0x00, 0x00, 0x00};

const Character font[] = {
    {0x0007, HAPPY},
    {0x0020, SPACE},
    {0x0021, EXCLAMATION_MARK},
    {0x0022, QUOTATION_MARK},
    {0x0023, NUMBER_SIGN},
    {0x0024, DOLLAR_SIGN},
    {0x0025, PERCENT_SIGN},
    {0x0026, AMPERSAND},
    {0x0027, APOSTROPHE},
    {0x0028, LEFT_PARENTHESIS},
    {0x0029, RIGHT_PARENTHESIS},
    {0x002a, ASTERISK},
    {0x002b, PLUS_SIGN},
    {0x002c, COMMA},
    {0x002d, HYPHEN_MINUS},
    {0x002e, FULL_STOP},
    {0x002f, SOLIDUS},
    {0x0030, DIGIT_0},
    {0x0031, DIGIT_1},
    {0x0032, DIGIT_2},
    {0x0033, DIGIT_3},
    {0x0034, DIGIT_4},
    {0x0035, DIGIT_5},
    {0x0036, DIGIT_6},
    {0x0037, DIGIT_7},
    {0x0038, DIGIT_8},
    {0x0039, DIGIT_9},
    {0x003a, COLON},
    {0x003b, SEMICOLON},
    {0x003c, LESS_THAN_SIGN},
    {0x003d, EQUALS_SIGN},
    {0x003e, GREATER_THAN_SIGN},
    {0x003f, QUESTION_MARK},
    {0x0040, COMMERCIAL_AT},
    {0x0041, A},
    {0x0042, B},
    {0x0043, C},
    {0x0044, D},
    {0x0045, E},
    {0x0046, F},
    {0x0047, G},
    {0x0048, H},
    {0x0049, I},
    {0x004a, J},
    {0x004b, K},
    {0x004c, L},
    {0x004d, M},
    {0x004e, N},
    {0x004f, O},
    {0x0050, P},
    {0x0051, Q},
    {0x0052, R},
    {0x0053, S},
    {0x0054, T},
    {0x0055, U},
    {0x0056, V},
    {0x0057, W},
    {0x0058, X},
    {0x0059, Y},
    {0x005a, Z},
    {0x005b, LEFT_SQUARE_BRACKET},
    {0x005c, REVERSE_SOLIDUS},
    {0x005d, RIGHT_SQUARE_BRACKET},
    {0x005e, CIRCUMFLEX_ACCENT},
    {0x005f, LOW_LINE},
    {0x0060, GRAVE_ACCENT},
    {0x0061, a},
    {0x0062, b},
    {0x0063, c},
    {0x0064, d},
    {0x0065, e},
    {0x0066, f},
    {0x0067, g},
    {0x0068, h},
    {0x0069, i},
    {0x006a, j},
    {0x006b, k},
    {0x006c, l},
    {0x006d, m},
    {0x006e, n},
    {0x006f, o},
    {0x0070, p},
    {0x0071, q},
    {0x0072, r},
    {0x0073, s},
    {0x0074, t},
    {0x0075, u},
    {0x0076, v},
    {0x0077, w},
    {0x0078, x},
    {0x0079, y},
    {0x007a, z},
    {0x007b, LEFT_CURLY_BRACKET},
    {0x007c, VERTICAL_LINE},
    {0x007d, RIGHT_CURLY_BRACKET},
    {0x007e, TILDE},
    {0x00e4, ae},
    {0x00f6, oe},
    {0x00fc, ue}
};

Character getCharacter(uint16_t code) {
    for (size_t i = 0; i < sizeof (font); i++) {
        if (font[i].code == code) {
            return font[i];
        }
    }

    return getCharacter(0x0020);
}