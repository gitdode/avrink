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
static void handleClear(char *data) {
    strtok(data, " ");
    char *end;
    uint8_t color = strtol(strtok(NULL, " "), &end, 16);
    
    setFrame(color);
}

/**
 * Writes one line of text to the given row and column.
 * @param data
 */
static void handleText(char *data) {
    strtok(data, " ");
    char *end;
    uint16_t row = strtol(strtok(NULL, " "), &end, 10);
    uint16_t col = strtol(strtok(NULL, " "), &end, 10);
    char *text = strtok(NULL, "\0");
    
    writeString(row, col, text);
}

/**
 * Writes the bitmap with the given index to the given row and column.
 * @param data
 */
static void handleBitmap(char *data) {
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
static void handleDemo(void) {
    setFrame(0x00);
    writeBitmap(1, 194, TUX);
    unifontDemo();
    display();
}

/**
 * Updates the display.
 */
static void handleUpdate(void) {
    display();
}

void handleCmd(char *data) {
    printString("\r\n");
    
    switch(*data) {
        case CMD_CLEAR: handleClear(data); break;
        case CMD_TEXT: handleText(data); break;
        case CMD_BITMAP: handleBitmap(data); break;
        case CMD_DEMO: handleDemo(); break;
        case CMD_UPDATE: handleUpdate(); break;
    }
}
