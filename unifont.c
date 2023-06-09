/* 
 * File:   unifont.c
 * Author: torsten.roemer@luniks.net
 * Unifont is part of the GNU Project: http://savannah.gnu.org/projects/unifont/
 *
 * Created on 8. April 2023, 20:52
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "font.h"
#include "unifont.h"
#include "utils.h"

#define WIDTH 8
#define HEIGHT 16

static const char demo1[] PROGMEM = "Hello GNU Unifont! \a";
static const char demo2[] PROGMEM = "!\"#$%&'()*+,-./0123456789";
static const char demo3[] PROGMEM = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char demo4[] PROGMEM = ":;<=>?@[\\]^_`{|}~×÷";
// static const char demo4[] PROGMEM = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿";
static const char demo5[] PROGMEM = "abcdefghijklmnopqrstuvwxyz";
static const char demo6[] PROGMEM = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞß";
static const char demo7[] PROGMEM = "àáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ";

/**
 * Demo text.
 */
static PGM_P const demoText[UNIFONT_DEMO_SIZE] PROGMEM = {
    demo1, demo2, demo3, demo4, demo5, demo6, demo7
};

char * getUnifontDemo(uint8_t line) {
    static char buf[64];
    strcpy_P(buf, (PGM_P)pgm_read_word(&demoText[line]));
    
    return buf;
}

static const uint8_t SPACE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t EXCLAMATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

static const uint8_t QUOTATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t NUMBER_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x12, 0x12, 0x12, 0x7E, 
    0x24, 0x24, 0x7E, 0x48, 0x48, 0x48, 0x00, 0x00};

static const uint8_t DOLLAR_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x3E, 0x49, 0x48, 
    0x38, 0x0E, 0x09, 0x49, 0x3E, 0x08, 0x00, 0x00};

static const uint8_t PERCENT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x31, 0x4A, 0x4A, 0x34, 
    0x08, 0x08, 0x16, 0x29, 0x29, 0x46, 0x00, 0x00};

static const uint8_t AMPERSAND[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x22, 0x14, 
    0x18, 0x29, 0x45, 0x42, 0x46, 0x39, 0x00, 0x00};

static const uint8_t APOSTROPHE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t LEFT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x00};

static const uint8_t RIGHT_PARENTHESIS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x20, 0x10, 0x10, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x00};

static const uint8_t ASTERISK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 
    0x2A, 0x1C, 0x2A, 0x49, 0x08, 0x00, 0x00, 0x00};

static const uint8_t PLUS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 
    0x08, 0x7F, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00};

static const uint8_t COMMA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10};

static const uint8_t HYPHEN_MINUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t FULL_STOP[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00};

static const uint8_t SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 
    0x08, 0x10, 0x10, 0x20, 0x40, 0x40, 0x00, 0x00};

static const uint8_t DIGIT_0[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x46, 
    0x4A, 0x52, 0x62, 0x42, 0x24, 0x18, 0x00, 0x00};

static const uint8_t DIGIT_1[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t DIGIT_2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x0C, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t DIGIT_3[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x1C, 0x02, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIGIT_4[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x14, 0x24, 
    0x44, 0x44, 0x7E, 0x04, 0x04, 0x04, 0x00, 0x00};

static const uint8_t DIGIT_5[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x02, 0x02, 0x02, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIGIT_6[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x20, 0x40, 0x40, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIGIT_7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t DIGIT_8[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIGIT_9[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x3E, 0x02, 0x02, 0x02, 0x04, 0x38, 0x00, 0x00};

static const uint8_t COLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};

static const uint8_t SEMICOLON[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x10, 0x00};

static const uint8_t LESS_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00};

static const uint8_t EQUALS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 
    0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00};

static const uint8_t GREATER_THAN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00};

static const uint8_t QUESTION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x02, 
    0x04, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00};

static const uint8_t COMMERCIAL_AT[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x22, 0x4A, 0x56, 
    0x52, 0x52, 0x52, 0x4E, 0x20, 0x1E, 0x00, 0x00};

static const uint8_t A[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t B[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x00, 0x00};

static const uint8_t C[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t D[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00};

static const uint8_t E[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t F[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

static const uint8_t G[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x4E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t H[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t I[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t J[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x04, 0x44, 0x44, 0x38, 0x00, 0x00};

static const uint8_t K[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 
    0x60, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

static const uint8_t L[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 
    0x40, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t M[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x66, 0x66, 
    0x5A, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t N[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 
    0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x00, 0x00};

static const uint8_t O[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t P[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

static const uint8_t Q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x5A, 0x66, 0x3C, 0x03, 0x00};

static const uint8_t R[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x42, 
    0x7C, 0x48, 0x44, 0x44, 0x42, 0x42, 0x00, 0x00};

static const uint8_t S[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x30, 0x0C, 0x02, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t T[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t U[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t V[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 
    0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00, 0x00};

static const uint8_t W[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x5A, 0x5A, 0x66, 0x66, 0x42, 0x42, 0x00, 0x00};

static const uint8_t X[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 
    0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x00, 0x00};

static const uint8_t Y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 
    0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t Z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x04, 
    0x08, 0x10, 0x20, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t LEFT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0E, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00};

static const uint8_t REVERSE_SOLIDUS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x20, 0x10, 
    0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x00, 0x00};

static const uint8_t RIGHT_SQUARE_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00};

static const uint8_t CIRCUMFLEX_ACCENT[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t LOW_LINE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00};

static const uint8_t GRAVE_ACCENT[] PROGMEM = {
    0x00, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t a[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t b[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x00, 0x00};

static const uint8_t c[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t d[] PROGMEM = {
    0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t e[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t f[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00};

static const uint8_t g[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3A, 0x44, 
    0x44, 0x44, 0x38, 0x20, 0x3C, 0x42, 0x42, 0x3C};

static const uint8_t h[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t i[] PROGMEM = {
    0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t j[] PROGMEM = {
    0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x0C, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x48, 0x30};

static const uint8_t k[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x44, 0x48, 
    0x50, 0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00};

static const uint8_t l[] PROGMEM = {
    0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t m[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00};

static const uint8_t n[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t o[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t p[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40};

static const uint8_t q[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A, 0x46, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x02, 0x02};

static const uint8_t r[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00};

static const uint8_t s[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x30, 0x0C, 0x02, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t t[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x7C, 
    0x10, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x00, 0x00};

static const uint8_t u[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t v[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x24, 0x24, 0x24, 0x18, 0x18, 0x00, 0x00};

static const uint8_t w[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x49, 
    0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00};

static const uint8_t x[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x24, 0x18, 0x18, 0x24, 0x42, 0x42, 0x00, 0x00};

static const uint8_t y[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

static const uint8_t z[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x02, 
    0x04, 0x08, 0x10, 0x20, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t LEFT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0C, 0x10, 0x10, 0x08, 0x08, 
    0x10, 0x20, 0x10, 0x08, 0x08, 0x10, 0x10, 0x0C};

static const uint8_t VERTICAL_LINE[] PROGMEM = {
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

static const uint8_t RIGHT_CURLY_BRACKET[] PROGMEM = {
    0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x10, 0x10, 
    0x08, 0x04, 0x08, 0x10, 0x10, 0x08, 0x08, 0x30};

static const uint8_t TILDE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x31, 0x49, 0x46, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t INVERTED_EXCLAMATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t CENT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3E, 0x49, 
    0x48, 0x48, 0x49, 0x3E, 0x08, 0x08, 0x00, 0x00};

static const uint8_t POUND_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x10, 0x10, 0x10, 
    0x7C, 0x10, 0x10, 0x10, 0x3E, 0x61, 0x00, 0x00};

static const uint8_t CURRENCY_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x3C, 0x24, 
    0x42, 0x42, 0x24, 0x3C, 0x42, 0x00, 0x00, 0x00};

static const uint8_t YEN_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x41, 0x22, 0x14, 0x08, 
    0x7F, 0x08, 0x7F, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t BROKEN_BAR[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 
    0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t SECTION_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x40, 0x3C, 
    0x42, 0x42, 0x3C, 0x02, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t COPYRIGHT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x99, 0xA5, 
    0xA1, 0xA1, 0xA5, 0x99, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t FEMININE_ORDINAL_INDICATOR[] PROGMEM = {
    0x00, 0x00, 0x1C, 0x02, 0x1E, 0x22, 0x1E, 0x00, 
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x12, 0x24, 
    0x24, 0x48, 0x24, 0x24, 0x12, 0x12, 0x00, 0x00};

static const uint8_t NOT_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x7E, 0x02, 0x02, 0x02, 0x00, 0x00};

static const uint8_t REGISTERED_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0xB9, 0xA5, 
    0xA5, 0xB9, 0xA9, 0xA5, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t MACRON[] PROGMEM = {
    0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t DEGREE_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t PLUS_MINUS_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7F, 
    0x08, 0x08, 0x08, 0x00, 0x7F, 0x00, 0x00, 0x00};

static const uint8_t SUPERSCRIPT_TWO[] PROGMEM = {
    0x00, 0x00, 0x00, 0x38, 0x44, 0x04, 0x18, 0x20, 
    0x40, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t SUPERSCRIPT_THREE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x38, 0x44, 0x04, 0x38, 0x04, 
    0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t ACUTE_ACCENT[] PROGMEM = {
    0x00, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t MICRO_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x66, 0x59, 0x40, 0x80};

static const uint8_t PILCROW_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x7A, 0x7A, 0x7A, 
    0x3A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00};

static const uint8_t MIDDLE_DOT[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t CEDILLA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x30};

static const uint8_t SUPERSCRIPT_ONE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 
    0x10, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t MASCULINE_ORDINAL_INDICATOR[] PROGMEM = {
    0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, 
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x48, 0x24, 
    0x24, 0x12, 0x24, 0x24, 0x48, 0x48, 0x00, 0x00};

static const uint8_t VULGAR_FRACTION_ONE_QUARTER[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x22, 0x62, 0x24, 0x28, 
    0x28, 0x12, 0x16, 0x2A, 0x4E, 0x42, 0x00, 0x00};

static const uint8_t VULGAR_FRACTION_ONE_HALF[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x22, 0x62, 0x24, 0x28, 
    0x28, 0x14, 0x1A, 0x22, 0x44, 0x4E, 0x00, 0x00};

static const uint8_t VULGAR_FRACTION_THREE_QUARTERS[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x62, 0x12, 0x24, 0x18, 
    0x68, 0x12, 0x16, 0x2A, 0x4E, 0x42, 0x00, 0x00};

static const uint8_t INVERTED_QUESTION_MARK[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x10, 
    0x10, 0x20, 0x40, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t A_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t A_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t A_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t A_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t A_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t A_RING[] PROGMEM = {
    0x18, 0x24, 0x18, 0x00, 0x18, 0x24, 0x24, 0x42, 
    0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t AE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x28, 0x48, 0x48, 
    0x7F, 0x48, 0x48, 0x48, 0x48, 0x4F, 0x00, 0x00};

static const uint8_t C_CEDILLA[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x40, 
    0x40, 0x40, 0x40, 0x42, 0x42, 0x3C, 0x08, 0x30};

static const uint8_t E_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t E_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t E_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t E_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x7E, 0x40, 0x40, 0x40, 
    0x7C, 0x40, 0x40, 0x40, 0x40, 0x7E, 0x00, 0x00};

static const uint8_t I_GRAVE[] PROGMEM = {
    0x18, 0x06, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t I_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t I_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t I_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t ETH[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 
    0xF2, 0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00};

static const uint8_t N_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 
    0x52, 0x4A, 0x4A, 0x46, 0x46, 0x42, 0x00, 0x00};

static const uint8_t O_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t O_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t O_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t O_TILDE[] PROGMEM = {
    0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t O_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t MULTIPLICATION_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 
    0x24, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 0x00};

static const uint8_t O_STROKE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x02, 0x3A, 0x44, 0x46, 0x4A, 
    0x4A, 0x52, 0x52, 0x62, 0x22, 0x5C, 0x40, 0x00};

static const uint8_t U_GRAVE[] PROGMEM = {
    0x30, 0x0C, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t U_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t U_CIRCUMFLEX[] PROGMEM = {
    0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t U_DIAERESIS[] PROGMEM = {
    0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t Y_ACUTE[] PROGMEM = {
    0x0C, 0x30, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 
    0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00};

static const uint8_t THORN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x78, 0x44, 0x42, 
    0x42, 0x44, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00};

static const uint8_t SHARP_S[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x48, 
    0x58, 0x44, 0x42, 0x42, 0x52, 0x4C, 0x00, 0x00};

static const uint8_t a_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t a_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t a_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t a_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t a_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t a_ring[] PROGMEM = {
    0x00, 0x18, 0x24, 0x18, 0x00, 0x00, 0x3C, 0x42, 
    0x02, 0x3E, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t ae[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x49, 
    0x09, 0x3F, 0x48, 0x48, 0x49, 0x3E, 0x00, 0x00};

static const uint8_t c_cedilla[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 
    0x40, 0x40, 0x40, 0x40, 0x42, 0x3C, 0x08, 0x30};

static const uint8_t e_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t e_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t e_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t e_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x7E, 0x40, 0x40, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t i_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t i_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t i_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t i_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x08, 
    0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00};

static const uint8_t eth[] PROGMEM = {
    0x00, 0x00, 0x32, 0x0C, 0x14, 0x22, 0x02, 0x3E, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t n_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00};

static const uint8_t o_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t o_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t o_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t o_tilde[] PROGMEM = {
    0x00, 0x00, 0x32, 0x4C, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t o_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3C, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00};

static const uint8_t DIVISION_SIGN[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
    0x00, 0x7E, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00};

static const uint8_t o_stroke[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3C, 0x46, 
    0x4A, 0x4A, 0x52, 0x52, 0x62, 0x3C, 0x40, 0x00};

static const uint8_t u_grave[] PROGMEM = {
    0x00, 0x00, 0x30, 0x0C, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t u_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t u_circumflex[] PROGMEM = {
    0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t u_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x42, 0x46, 0x3A, 0x00, 0x00};

static const uint8_t y_acute[] PROGMEM = {
    0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

static const uint8_t thorn[] PROGMEM = {
    0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5C, 0x62, 
    0x42, 0x42, 0x42, 0x42, 0x62, 0x5C, 0x40, 0x40};

static const uint8_t y_diaeresis[] PROGMEM = {
    0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 
    0x42, 0x42, 0x42, 0x26, 0x1A, 0x02, 0x02, 0x3C};

static const uint8_t SMILING_FACE[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0xA5, 
    0x81, 0xA5, 0x99, 0x42, 0x3C, 0x00, 0x00, 0x00};

static const uint8_t YIN_YANG[] PROGMEM = {
    0x07, 0xE0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 
    0x40, 0x02, 0x9C, 0x31, 0xBE, 0x31, 0xFF, 0x03, 
    0xE7, 0x83, 0xE7, 0xC7, 0xFF, 0xFF, 0x7F, 0xFE, 
    0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, 0x07, 0xE0  
};

static const Glyph glyphs[] PROGMEM = {
    // bell (\a) maps to SMILING_FACE
    {0x0007, WIDTH, SMILING_FACE},
    {0x0020, WIDTH, SPACE},
    {0x0021, WIDTH, EXCLAMATION_MARK},
    {0x0022, WIDTH, QUOTATION_MARK},
    {0x0023, WIDTH, NUMBER_SIGN},
    {0x0024, WIDTH, DOLLAR_SIGN},
    {0x0025, WIDTH, PERCENT_SIGN},
    {0x0026, WIDTH, AMPERSAND},
    {0x0027, WIDTH, APOSTROPHE},
    {0x0028, WIDTH, LEFT_PARENTHESIS},
    {0x0029, WIDTH, RIGHT_PARENTHESIS},
    {0x002a, WIDTH, ASTERISK},
    {0x002b, WIDTH, PLUS_SIGN},
    {0x002c, WIDTH, COMMA},
    {0x002d, WIDTH, HYPHEN_MINUS},
    {0x002e, WIDTH, FULL_STOP},
    {0x002f, WIDTH, SOLIDUS},
    {0x0030, WIDTH, DIGIT_0},
    {0x0031, WIDTH, DIGIT_1},
    {0x0032, WIDTH, DIGIT_2},
    {0x0033, WIDTH, DIGIT_3},
    {0x0034, WIDTH, DIGIT_4},
    {0x0035, WIDTH, DIGIT_5},
    {0x0036, WIDTH, DIGIT_6},
    {0x0037, WIDTH, DIGIT_7},
    {0x0038, WIDTH, DIGIT_8},
    {0x0039, WIDTH, DIGIT_9},
    {0x003a, WIDTH, COLON},
    {0x003b, WIDTH, SEMICOLON},
    {0x003c, WIDTH, LESS_THAN_SIGN},
    {0x003d, WIDTH, EQUALS_SIGN},
    {0x003e, WIDTH, GREATER_THAN_SIGN},
    {0x003f, WIDTH, QUESTION_MARK},
    {0x0040, WIDTH, COMMERCIAL_AT},
    {0x0041, WIDTH, A},
    {0x0042, WIDTH, B},
    {0x0043, WIDTH, C},
    {0x0044, WIDTH, D},
    {0x0045, WIDTH, E},
    {0x0046, WIDTH, F},
    {0x0047, WIDTH, G},
    {0x0048, WIDTH, H},
    {0x0049, WIDTH, I},
    {0x004a, WIDTH, J},
    {0x004b, WIDTH, K},
    {0x004c, WIDTH, L},
    {0x004d, WIDTH, M},
    {0x004e, WIDTH, N},
    {0x004f, WIDTH, O},
    {0x0050, WIDTH, P},
    {0x0051, WIDTH, Q},
    {0x0052, WIDTH, R},
    {0x0053, WIDTH, S},
    {0x0054, WIDTH, T},
    {0x0055, WIDTH, U},
    {0x0056, WIDTH, V},
    {0x0057, WIDTH, W},
    {0x0058, WIDTH, X},
    {0x0059, WIDTH, Y},
    {0x005a, WIDTH, Z},
    {0x005b, WIDTH, LEFT_SQUARE_BRACKET},
    {0x005c, WIDTH, REVERSE_SOLIDUS},
    {0x005d, WIDTH, RIGHT_SQUARE_BRACKET},
    {0x005e, WIDTH, CIRCUMFLEX_ACCENT},
    {0x005f, WIDTH, LOW_LINE},
    {0x0060, WIDTH, GRAVE_ACCENT},
    {0x0061, WIDTH, a},
    {0x0062, WIDTH, b},
    {0x0063, WIDTH, c},
    {0x0064, WIDTH, d},
    {0x0065, WIDTH, e},
    {0x0066, WIDTH, f},
    {0x0067, WIDTH, g},
    {0x0068, WIDTH, h},
    {0x0069, WIDTH, i},
    {0x006a, WIDTH, j},
    {0x006b, WIDTH, k},
    {0x006c, WIDTH, l},
    {0x006d, WIDTH, m},
    {0x006e, WIDTH, n},
    {0x006f, WIDTH, o},
    {0x0070, WIDTH, p},
    {0x0071, WIDTH, q},
    {0x0072, WIDTH, r},
    {0x0073, WIDTH, s},
    {0x0074, WIDTH, t},
    {0x0075, WIDTH, u},
    {0x0076, WIDTH, v},
    {0x0077, WIDTH, w},
    {0x0078, WIDTH, x},
    {0x0079, WIDTH, y},
    {0x007a, WIDTH, z},
    {0x007b, WIDTH, LEFT_CURLY_BRACKET},
    {0x007c, WIDTH, VERTICAL_LINE},
    {0x007d, WIDTH, RIGHT_CURLY_BRACKET},
    {0x007e, WIDTH, TILDE},
    // skipped NO-BREAK SPACE
    {0x00a1, WIDTH, INVERTED_EXCLAMATION_MARK},
    {0x00a2, WIDTH, CENT_SIGN},
    {0x00a3, WIDTH, POUND_SIGN},
    {0x00a4, WIDTH, CURRENCY_SIGN},
    {0x00a5, WIDTH, YEN_SIGN},
    {0x00a6, WIDTH, BROKEN_BAR},
    {0x00a7, WIDTH, SECTION_SIGN},
    {0x00a8, WIDTH, DIAERESIS},
    {0x00a9, WIDTH, COPYRIGHT_SIGN},
    {0x00aa, WIDTH, FEMININE_ORDINAL_INDICATOR},
    {0x00ab, WIDTH, LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK},
    {0x00ac, WIDTH, NOT_SIGN},
    // skipped SOFT HYPHEN
    {0x00ae, WIDTH, REGISTERED_SIGN},
    {0x00af, WIDTH, MACRON},
    {0x00b0, WIDTH, DEGREE_SIGN},
    {0x00b1, WIDTH, PLUS_MINUS_SIGN},
    {0x00b2, WIDTH, SUPERSCRIPT_TWO},
    {0x00b3, WIDTH, SUPERSCRIPT_THREE},
    {0x00b4, WIDTH, ACUTE_ACCENT},
    {0x00b5, WIDTH, MICRO_SIGN},
    {0x00b6, WIDTH, PILCROW_SIGN},
    {0x00b7, WIDTH, MIDDLE_DOT},
    {0x00b8, WIDTH, CEDILLA},
    {0x00b9, WIDTH, SUPERSCRIPT_ONE},
    {0x00ba, WIDTH, MASCULINE_ORDINAL_INDICATOR},
    {0x00bb, WIDTH, RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK},
    {0x00bc, WIDTH, VULGAR_FRACTION_ONE_QUARTER},
    {0x00bd, WIDTH, VULGAR_FRACTION_ONE_HALF},
    {0x00be, WIDTH, VULGAR_FRACTION_THREE_QUARTERS},
    {0x00bf, WIDTH, INVERTED_QUESTION_MARK},
    {0x00c0, WIDTH, A_GRAVE},
    {0x00c1, WIDTH, A_ACUTE},
    {0x00c2, WIDTH, A_CIRCUMFLEX},
    {0x00c3, WIDTH, A_TILDE},
    {0x00c4, WIDTH, A_DIAERESIS},
    {0x00c5, WIDTH, A_RING},
    {0x00c6, WIDTH, AE},
    {0x00c7, WIDTH, C_CEDILLA},
    {0x00c8, WIDTH, E_GRAVE},
    {0x00c9, WIDTH, E_ACUTE},
    {0x00ca, WIDTH, E_CIRCUMFLEX},
    {0x00cb, WIDTH, E_DIAERESIS},
    {0x00cc, WIDTH, I_GRAVE},
    {0x00cd, WIDTH, I_ACUTE},
    {0x00ce, WIDTH, I_CIRCUMFLEX},
    {0x00cf, WIDTH, I_DIAERESIS},
    {0x00d0, WIDTH, ETH},
    {0x00d1, WIDTH, N_TILDE},
    {0x00d2, WIDTH, O_GRAVE},
    {0x00d3, WIDTH, O_ACUTE},
    {0x00d4, WIDTH, O_CIRCUMFLEX},
    {0x00d5, WIDTH, O_TILDE},
    {0x00d6, WIDTH, O_DIAERESIS},
    {0x00d7, WIDTH, MULTIPLICATION_SIGN},
    {0x00d8, WIDTH, O_STROKE},
    {0x00d9, WIDTH, U_GRAVE},
    {0x00da, WIDTH, U_ACUTE},
    {0x00db, WIDTH, U_CIRCUMFLEX},
    {0x00dc, WIDTH, U_DIAERESIS},
    {0x00dd, WIDTH, Y_ACUTE},
    {0x00de, WIDTH, THORN},
    {0x00df, WIDTH, SHARP_S},
    {0x00e0, WIDTH, a_grave},
    {0x00e1, WIDTH, a_acute},
    {0x00e2, WIDTH, a_circumflex},
    {0x00e3, WIDTH, a_tilde},
    {0x00e4, WIDTH, a_diaeresis},
    {0x00e5, WIDTH, a_ring},
    {0x00e6, WIDTH, ae},
    {0x00e7, WIDTH, c_cedilla},
    {0x00e8, WIDTH, e_grave},
    {0x00e9, WIDTH, e_acute},
    {0x00ea, WIDTH, e_circumflex},
    {0x00eb, WIDTH, e_diaeresis},
    {0x00ec, WIDTH, i_grave},
    {0x00ed, WIDTH, i_acute},
    {0x00ee, WIDTH, i_circumflex},
    {0x00ef, WIDTH, i_diaeresis},
    {0x00f0, WIDTH, eth},
    {0x00f1, WIDTH, n_tilde},
    {0x00f2, WIDTH, o_grave},
    {0x00f3, WIDTH, o_acute},
    {0x00f4, WIDTH, o_circumflex},
    {0x00f5, WIDTH, o_tilde},
    {0x00f6, WIDTH, o_diaeresis},
    {0x00f7, WIDTH, DIVISION_SIGN},
    {0x00f8, WIDTH, o_stroke},
    {0x00f9, WIDTH, u_grave},
    {0x00fa, WIDTH, u_acute},
    {0x00fb, WIDTH, u_circumflex},
    {0x00fc, WIDTH, u_diaeresis},
    {0x00fd, WIDTH, y_acute},
    {0x00fe, WIDTH, thorn},
    {0x00ff, WIDTH, y_diaeresis}
};

const Font getUnifont(void) {
    const Font unifont = {glyphs, ARRAY_LENGTH(glyphs), HEIGHT};
    
    return unifont;
}