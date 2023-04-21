/* 
 * File:   cmd.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#ifndef CMD_H
#define CMD_H

#define CMD_TEXT    "text"
#define CMD_BITMAP  "bitmap"
#define CMD_ROW     "row"
#define CMD_COL     "col"

/**
 * Initial attempt to send text via USART to the display.
 * @param data
 */
void handle(char *data);

#endif /* CMD_H */

