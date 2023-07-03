/* 
 * File:   cmd.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#ifndef CMD_H
#define CMD_H

/** Clear frame buffer: 'c <0xff|0x00>'. */
#define CMD_CLEAR       'c'
/** Display one line of text: 't <row> <col> <font> <text>'. */
#define CMD_TEXT        't'
/** Display a bitmap: 'b <row> <col> <index>'. */
#define CMD_BITMAP      'b'
/** Display Unifont demo: 'd'. */
#define CMD_DEMO        'd'
/** Update display (full or fast mode): 'u <0|1>'. */
#define CMD_UPDATE      'u'

#define FONT_UNIFONT    'u'
#define FONT_DEJAVU     'd'

/**
 * Handles the given command.
 * @param data
 */
void handleCmd(char *data);

#endif /* CMD_H */
