/* 
 * File:   cmd.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#ifndef CMD_H
#define CMD_H

#define CMD_CLEAR   'c' // clear frame buffer: 'c <0xff|0x00>'
#define CMD_TEXT    't' // display one line of text: 't <row> <col> <text>'
#define CMD_BITMAP  'b' // display a bitmap: 'b <row> <col> <index>'
#define CMD_DEMO    'd' // display Unifont demo: 'd'
#define CMD_UPDATE  'u' // update display: 'u'

/**
 * Handles the given command.
 * @param data
 */
void handleCmd(char *data);

#endif /* CMD_H */
