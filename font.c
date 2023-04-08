/* 
 * File:   font.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 8. April 2023, 20:52
 */

#include <stdio.h>
#include <avr/pgmspace.h>
#include "font.h"

const char happy[] PROGMEM = {
    0b11111111, 0b11111111,
    0b11111111, 0b11111111,
    0b11100111, 0b11100111,
    0b11111111, 0b11111111,
    0b11111111, 0b11111111,
    0b11100111, 0b11100111,
    0b11111111, 0b11111111,
    0b11111111, 0b11111111,
    0b11111111, 0b11111111,
    0b10011111, 0b10000111,
    0b11100111, 0b11110011,
    0b11110011, 0b11110011,
    0b11110011, 0b11110011,
    0b11110011, 0b11100111,
    0b10000111, 0b10011111,
    0b11111111, 0b11111111
};

const Character font[] = {
    {EMOJI_HAPPY, happy, 16}
};

Character getCharacter(uint16_t code) {
    for (size_t i = 0; i < sizeof (font); i++) {
        if (font[i].code == code) {
            return font[i];
        }
    }

    return getCharacter(EMOJI_HAPPY);
}