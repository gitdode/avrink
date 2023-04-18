/* 
 * File:   cmd.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#include "usart.h"
#include "eink.h"
#include "display.h"
#include "bitmaps.h"

extern uint8_t cmd;
extern uint8_t row;
extern uint8_t col;

void handle(char *data) {
    char buf[64];
    snprintf(buf, sizeof (buf), "%s", data);
    // printString(buf);

    setFrame(0x00);
    writeBitmap(4, 194, TUX);
    writeString(0, 0, buf);

    initDisplay();
    resetAddressCounter();
    sramToDisplay();
    updateDisplay();
}