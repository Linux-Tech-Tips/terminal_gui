/** 
 * @file terminal_f.h 
 * @brief header file declaring custom functions for terminal GUI using ANSI Sequences
*/
#ifndef ESC_FUNC_H
#define ESC_FUNC_H


/* Includes */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h> /* UNIX std library - not multiplatform */
#include <sys/ioctl.h>
#include <poll.h>


/* === ESCAPE CODE CONSTANT DEFINITIONS === */

#define ESCAPE "\x1b["
#define ESCAPE_PURE "\x1b"
#define NO_CODE -1

/* Foreground colors */
#define FG_BLACK 30
#define FG_RED 31
#define FG_GREEN 32
#define FG_YELLOW 33
#define FG_BLUE 34
#define FG_MAGENTA 35
#define FG_CYAN 36
#define FG_WHITE 37
#define FG_DEFAULT 39

/* Background colors */
#define BG_BLACK 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_MAGENTA 45
#define BG_CYAN 46
#define BG_WHITE 47
#define BG_DEFAULT 49

/* Styles */
#define STYLE_BOLD 1
#define STYLE_FAINT 2
#define STYLE_ITALIC 3
#define STYLE_UNDERLINE 4
#define STYLE_BLINKING 5
#define STYLE_REVERSE 7
#define STYLE_HIDDEN 8
#define STYLE_STRIKETHROUGH 9

/* Directions */
#define UP 'A'
#define DOWN 'B'
#define LEFT 'D'
#define RIGHT 'C'

/* Line erase options */
#define LINE_TO_END 0
#define LINE_FROM_START 1
#define LINE_ALL 2


/* === TERMINAL FUNCTIONS === */

/** Resets all modes (styles and colors) */
void modeReset();

/** Sets the mode of the cursor to the selected style, foreground and background colors */
void modeSet(int style, int fgColor, int bgColor);

/** Sets the mode of the cursor to 256-color, using the provided color code 
 *  @param bg boolean value deciding whether the color is set to background (1) or foreground (0)
*/
void mode256Color(int bg, int colorCode);

/** Erases the screen */
void erase();

/** Erases characters on the current line based on the provided line type 
 *  @param lineType recommended to use the provided constants: LINE_TO_END | LINE_FROM_START | LINE_ALL
*/
void eraseLine(int lineType);

/** Move the cursor to the home position (0,0) */
void cursorHome();

/** Move the cursor to the specified column and line (x, y) */
void cursorMoveTo(int column, int line);

/** Move the cursor by the specified amount in the set direction
 *  @param dir for the direction, recommended to use the provided constants: UP | DOWN | LEFT | RIGHT
 */
void cursorMoveBy(char dir, int amount);

/** Saves the current terminal dimensions into the parameters x and y */
void getTerminalSize(int * x, int * y);

/** Sets the required terminal options for non-blocking read */
void startKeys();

/** Resets the terminal options from non-blocking read back to normal */
void endKeys();

/** Non-blocking character read, reads keyboard input asynchronously while the program is running in the terminal 
 * Before using this function, set the required settings using the startKeys() function. Afterwards, reset the options using endKeys()
 * @returns 1 if any characters read successfully, otherwise 0
*/
short nbRead(char * buffer, size_t maxToRead);

/** Sets the cursor to be invisible */
void cursorHide();
/** Sets the cursor to be visible */
void cursorShow();

/** Saves the current state and options of the terminal */
void screenSave();
/** Resets the current state and options of the terminal */
void screenRestore();

#endif
