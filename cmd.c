/* 
 * File:   cmd.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#include <string.h>
#include <stdlib.h>
#include "cmd.h"
#include "usart.h"
#include "eink.h"
#include "display.h"
#include "bitmaps.h"

/**
 * Sets the frame buffer to black (0xff) or white (0x00).
 * @param data
 */
static void clear(char *data) {
    strtok(data, " ");
    char *end;
    uint8_t color = strtol(strtok(NULL, " "), &end, 16);
    
    setFrame(color);
}

/**
 * Writes one line of text to the given row and column.
 * @param data
 */
static void text(char *data) {
    strtok(data, " ");
    char *end;
    uint16_t row = strtol(strtok(NULL, " "), &end, 10);
    uint16_t col = strtol(strtok(NULL, " "), &end, 10);
    char *font = strtok(NULL, " ");
    char *text = strtok(NULL, "\0");
    
    // TODO improve
    switch(*font) {
        case 'u': writeString(row, col, UNIFONT, text); break;
        case 'd': writeString(row, col, DEJAVU, text); break;
        default: break;
    }
}

/**
 * Writes the bitmap with the given index to the given row and column.
 * @param data
 */
static void bitmap(char *data) {
    strtok(data, " ");
    char *end;
    uint16_t row = strtol(strtok(NULL, " "), &end, 10);
    uint16_t col = strtol(strtok(NULL, " "), &end, 10);
    uint8_t index = strtol(strtok(NULL, " "), &end, 10);
    
    writeBitmap(row, col, index);
}

/**
 * Writes the Unifont demo.
 */
static void demo(void) {
    setFrame(0x00);
    writeBitmap(1, 198, TUX);
    unifontDemo();
    display();
}

/**
 * Updates the display.
 */
static void update(void) {
    display();
}

void handleCmd(char *data) {
    printString("\r\n");
    
    switch(*data) {
        case CMD_CLEAR:  clear(data); break;
        case CMD_TEXT:   text(data); break;
        case CMD_BITMAP: bitmap(data); break;
        case CMD_DEMO:   demo(); break;
        case CMD_UPDATE: update(); break;
        default: break;
    }
}
