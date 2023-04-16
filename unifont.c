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
#include "utils.h"

static const char demoLine1[] PROGMEM = "Hello GNU Unifont! \a";
static const char demoLine2[] PROGMEM = "!\"#$%&'()*+,-./0123456789";
static const char demoLine3[] PROGMEM = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char demoLine4[] PROGMEM = ":;<=>?@[\\]^_`{|}~¿×÷";
static const char demoLine5[] PROGMEM = "abcdefghijklmnopqrstuvwxyz";
static const char demoLine6[] PROGMEM = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞß";
static const char demoLine7[] PROGMEM = "àáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ";

/**
 * Demo text.
 */
static PGM_P const demoText[DEMO_TEXT_SIZE] PROGMEM = {
    demoLine1,
    demoLine2,
    demoLine3,
    demoLine4,
    demoLine5,
    demoLine6,
    demoLine7
};

char * getDemoText(uint8_t line) {
    static char buf[64];
    strcpy_P(buf, (PGM_P)pgm_read_word(&demoText[line]));
    
    return buf;
}

const uint8_t SPACE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t EXCLAMATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

const uint8_t QUOTATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t NUMBER_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x12, 0x12, 0x12, 0x7E, 
    0x24, 0x24, 0x7E, 0x48, 0x48, 0x48, 0x00, 0x00};

const uint8_t DOLLAR_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x3E, 0x49, 0x48, 
    0x38, 0x0E, 0x09, 0x49, 0x3E, 0x08, 0x00, 0x00};

const uint8_t PERCENT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x31, 0x4A, 0x4A, 0x34, 
    0x08, 0x08, 0x16, 0x29, 0x29, 0x46, 0x00, 0x00};

const uint8_t AMPERSAND[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x22, 0x14, 
    0x18, 0x29, 0x45, 0x42, 0x46, 0x39, 0x00, 0x00};

const uint8_t APOSTROPHE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t LEFT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x00};

const uint8_t RIGHT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x20, 0x10, 0x10, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x00};

const uint8_t ASTERISK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 
    0x2A, 0x1C, 0x2A, 0x49, 0x08, 0x00, 0x00, 0x00};

const uint8_t PLUS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 
    0x08, 0x7F, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00};

const uint8_t COMMA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10};

const uint8_t HYPHEN_MINUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t FULL_STOP[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00};

const uint8_t SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 
    0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x00, 0x00};

const uint8_t DIGIT_0[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x46, 
    0x4A, 0x52, 0x62, 0x42, 0x24, 0x18, 0x00, 0x00};

const uint8_t DIGIT_1[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t DIGIT_2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x0C, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t DIGIT_3[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x1C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t DIGIT_4[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 
    0x44, 0x44, 0x7E, 0x04, 0x04, 0x04, 0x00, 0x00};

const uint8_t DIGIT_5[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x02, 0x02, 0x02, 0x42, 0x3C, 0x00, 0x00};

const uint8_t DIGIT_6[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x20, 0x40, 0x40, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t DIGIT_7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const uint8_t DIGIT_8[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t DIGIT_9[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3E, 0x02, 0x02, 0x02, 0x04, 0x38, 0x00, 0x00};

const uint8_t COLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};

const uint8_t SEMICOLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10, 0x00};

const uint8_t LESS_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00};

const uint8_t EQUALS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 
    0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00};

const uint8_t GREATER_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00};

const uint8_t QUESTION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x04, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

const uint8_t COMMERCIAL_AT[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x4A, 0x56, 
    0x52, 0x52, 0x52, 0x4E, 0x20, 0x1E, 0x00, 0x00};

const uint8_t A[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t B[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x00, 0x00};

const uint8_t C[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t D[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00};

const uint8_t E[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t F[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const uint8_t G[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x4E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t H[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t I[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t J[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00, 0x00};

const uint8_t K[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 
    0x60, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

const uint8_t L[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t M[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x66, 0x66, 
    0x5A, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t N[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 
    0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x00, 0x00};

const uint8_t O[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t P[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const uint8_t Q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x5A, 0x66, 0x3C, 0x03, 0x00};

const uint8_t R[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x48, 0x44, 0x44, 0x42, 0x42, 0x00, 0x00};

const uint8_t S[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x30, 0x0C, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t T[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const uint8_t U[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t V[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 
    0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00, 0x00};

const uint8_t W[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x5A, 0x5A, 0x66, 0x66, 0x42, 0x42, 0x00, 0x00};

const uint8_t X[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 
    0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x00, 0x00};

const uint8_t Y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 
    0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const uint8_t Z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t LEFT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0E, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00};

const uint8_t REVERSE_SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x20, 0x10, 
    0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x00, 0x00};

const uint8_t RIGHT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00};

const uint8_t CIRCUMFLEX_ACCENT[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t LOW_LINE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00};

const uint8_t GRAVE_ACCENT[] PROGMEM = {
    0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t a[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t b[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x00, 0x00};

const uint8_t c[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t d[] PROGMEM = {
    0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t e[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t f[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};

const uint8_t g[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3A, 0x44, 
    0x44, 0x44, 0x38, 0x20, 0x3C, 0x42, 0x42, 0x3C};

const uint8_t h[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t i[] PROGMEM = {
    0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t j[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x0C, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x48, 0x30};

const uint8_t k[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x44, 0x48, 
    0x50, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

const uint8_t l[] PROGMEM = {
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t m[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00};

const uint8_t n[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t o[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t p[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40};

const uint8_t q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02};

const uint8_t r[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

const uint8_t s[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x30, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00};

const uint8_t t[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x00, 0x00};

const uint8_t u[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t v[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x24, 0x24, 0x24, 0x18, 0x18, 0x00, 0x00};

const uint8_t w[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00};

const uint8_t x[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x24, 0x18, 0x18, 0x24, 0x42, 0x42, 0x00, 0x00};

const uint8_t y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

const uint8_t z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 
    0x04, 0x08, 0x10, 0x20, 0x40, 0x7E, 0x00, 0x00};

const uint8_t LEFT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x08, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x08, 0x10, 0x10, 0x0C};

const uint8_t VERTICAL_LINE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

const uint8_t RIGHT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x10, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x10, 0x08, 0x08, 0x30};

const uint8_t TILDE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x31, 0x49, 0x46, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t INVERTED_QUESTION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x10, 
    0x10, 0x20, 0x40, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t A_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t A_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t A_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t A_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t A_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t A_RING[] PROGMEM = {
    0x18, 0x24, 0x18, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t AE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x28, 0x48, 0x48, 
    0x7F, 0x48, 0x48, 0x48, 0x48, 0x4F, 0x00, 0x00};

const uint8_t C_CEDILLA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x08, 0x30};

const uint8_t E_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t E_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t E_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t E_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

const uint8_t I_GRAVE[] PROGMEM = {
    0x18, 0x06, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t I_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t I_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t I_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t ETH[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 
    0xF2, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00};

const uint8_t N_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 
    0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x00, 0x00};

const uint8_t O_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t O_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t O_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t O_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t O_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t MULTIPLICATION_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 
    0x24, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 0x00};

const uint8_t O_STROKE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x02, 0x3A, 0x44, 0x46, 0x4A, 
    0x4A, 0x52, 0x52, 0x62, 0x22, 0x5C, 0x40, 0x00};

const uint8_t U_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t U_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t U_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t U_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t Y_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 
    0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

const uint8_t THORN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x78, 0x44, 0x42, 
    0x42, 0x44, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00};

const uint8_t SHARP_S[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x48, 
    0x58, 0x44, 0x42, 0x42, 0x52, 0x4C, 0x00, 0x00};

const uint8_t a_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t a_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t a_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t a_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t a_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t a_ring[] PROGMEM = {
    0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t ae[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x49, 
    0x09, 0x3F, 0x48, 0x48, 0x49, 0x3E, 0x00, 0x00};

const uint8_t c_cedilla[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x08, 0x30};

const uint8_t e_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t e_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t e_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t e_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

const uint8_t i_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t i_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t i_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t i_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

const uint8_t eth[] PROGMEM = {
    0x00, 0x00, 0x32, 0x0C, 0x14, 0x22, 0x02, 0x3E, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t n_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

const uint8_t o_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t o_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t o_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t o_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t o_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

const uint8_t DIVISION_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
    0x00, 0x7E, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00};

const uint8_t o_stroke[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3C, 0x46, 
    0x4A, 0x4A, 0x52, 0x52, 0x62, 0x3C, 0x40, 0x00};

const uint8_t u_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t u_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t u_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t u_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

const uint8_t y_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

const uint8_t thorn[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40};

const uint8_t y_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

const uint8_t SMILING_FACE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0xA5, 
    0x81, 0xA5, 0x99, 0x42, 0x3C, 0x00, 0x00, 0x00};

const uint8_t YIN_YANG[] PROGMEM = {
    0x07, 0xE0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 
    0x40, 0x02, 0x9C, 0x31, 0xBE, 0x31, 0xFF, 0x03, 
    0xE7, 0x83, 0xE7, 0xC7, 0xFF, 0xFF, 0x7F, 0xFE, 
    0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, 0x07, 0xE0  
};

const Character chars[] PROGMEM = {
    // bell (\a) maps to SMILING_FACE
    {0x0007, SMILING_FACE},
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
    // skipped some probably not so much needed signs here
    {0x00bf, INVERTED_QUESTION_MARK},
    {0x00c0, A_GRAVE},
    {0x00c1, A_ACUTE},
    {0x00c2, A_CIRCUMFLEX},
    {0x00c3, A_TILDE},
    {0x00c4, A_DIAERESIS},
    {0x00c5, A_RING},
    {0x00c6, AE},
    {0x00c7, C_CEDILLA},
    {0x00c8, E_GRAVE},
    {0x00c9, E_ACUTE},
    {0x00ca, E_CIRCUMFLEX},
    {0x00cb, E_DIAERESIS},
    {0x00cc, I_GRAVE},
    {0x00cd, I_ACUTE},
    {0x00ce, I_CIRCUMFLEX},
    {0x00cf, I_DIAERESIS},
    {0x00d0, ETH},
    {0x00d1, N_TILDE},
    {0x00d2, O_GRAVE},
    {0x00d3, O_ACUTE},
    {0x00d4, O_CIRCUMFLEX},
    {0x00d5, O_TILDE},
    {0x00d6, O_DIAERESIS},
    {0x00d7, MULTIPLICATION_SIGN},
    {0x00d8, O_STROKE},
    {0x00d9, U_GRAVE},
    {0x00da, U_ACUTE},
    {0x00db, U_CIRCUMFLEX},
    {0x00dc, U_DIAERESIS},
    {0x00dd, Y_ACUTE},
    {0x00de, THORN},
    {0x00df, SHARP_S},
    {0x00e0, a_grave},
    {0x00e1, a_acute},
    {0x00e2, a_circumflex},
    {0x00e3, a_tilde},
    {0x00e4, a_diaeresis},
    {0x00e5, a_ring},
    {0x00e6, ae},
    {0x00e7, c_cedilla},
    {0x00e8, e_grave},
    {0x00e9, e_acute},
    {0x00ea, e_circumflex},
    {0x00eb, e_diaeresis},
    {0x00ec, i_grave},
    {0x00ed, i_acute},
    {0x00ee, i_circumflex},
    {0x00ef, i_diaeresis},
    {0x00f0, eth},
    {0x00f1, n_tilde},
    {0x00f2, o_grave},
    {0x00f3, o_acute},
    {0x00f4, o_circumflex},
    {0x00f5, o_tilde},
    {0x00f6, o_diaeresis},
    {0x00f7, DIVISION_SIGN},
    {0x00f8, o_stroke},
    {0x00f9, u_grave},
    {0x00fa, u_acute},
    {0x00fb, u_circumflex},
    {0x00fc, u_diaeresis},
    {0x00fd, y_acute},
    {0x00fe, thorn},
    {0x00ff, y_diaeresis}
};

Character getCharacter(uint16_t code) {
    size_t length = ARRAY_LENGTH(chars);
    for (size_t i = 0; i < length; i++) {
        if (pgm_read_word(&chars[i].code) == code) {
            static Character character;
            memcpy_P(&character, &chars[i], sizeof (Character));
            
            return character;
        }
    }
    
    // return question mark if unknown code point
    return getCharacter(0x003f);
}