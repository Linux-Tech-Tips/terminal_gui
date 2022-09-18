#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // UNIX std library - not multiplatform
#include <sys/ioctl.h>

#include "terminal_f.h"

/* Unique code constants */
const int NO_CODE = 0;
// FG COLORS
const int FG_BLACK = 30;
const int FG_RED = 31;
const int FG_GREEN = 32;
const int FG_YELLOW = 33;
const int FG_BLUE = 34;
const int FG_MAGENTA = 35;
const int FG_CYAN = 36;
const int FG_WHITE = 37;
const int FG_DEFAULT = 39;
// BG COLORS
const int BG_BLACK = 40;
const int BG_RED = 41;
const int BG_GREEN = 42;
const int BG_YELLOW = 43;
const int BG_BLUE = 44;
const int BG_MAGENTA = 45;
const int BG_CYAN = 46;
const int BG_WHITE = 47;
const int BG_DEFAULT = 49;
// STYLES
const int STYLE_BOLD = 1;
const int STYLE_FAINT = 2;
const int STYLE_ITALIC = 3;
const int STYLE_UNDERLINE = 4;
const int STYLE_BLINKING = 5;
const int STYLE_REVERSE = 7;
const int STYLE_HIDDEN = 8;
const int STYLE_STRIKETHROUGH = 9;
// DIRS
const char UP = 'A';
const char DOWN = 'B';
const char LEFT = 'D';
const char RIGHT = 'C';
// LINE ERASE TYPES
const int LINE_TO_END = 0;
const int LINE_FROM_START = 1;
const int LINE_ALL = 2;

// TERMINAL FUNCTIONS

/* Prints out the escape character into the console */
void escape(bool withBracket) {
    printf("\x1b");
    if(withBracket) printf("[");
}

/* Prints out an escape sequence, starting with the escape character, then an open bracket, followed with the input text */
void escape2(char * text) {
    printf("\x1b[%s", text);
}

/* Resets all modes (styles and colors) */
void modeReset() {
    escape2("0m");
}

/* Sets the mode */
void modeSet(int style, int fgColor, int bgColor) {
    escape(true);
    if(style != NO_CODE) printf("%i", style);
    printf(";");
    if(fgColor != NO_CODE) printf("%i", fgColor);
    if(bgColor != NO_CODE) printf(";%i", bgColor);
    printf("m");
}

/* Sets a 256 color mode */
void mode256Color(bool bg, int colorCode) {
	escape(true);
	int mode = bg ? 48 : 38;
	printf("%i;5;%im", mode, colorCode);
}

/* Erases the screen */
void erase() {
	escape2("2J");
}

/* Erases on the current line, according to the specified variable */
void eraseLine(int lineType) {
    escape(true);
    printf("%iK", lineType);
}

/* Move cursor to home position (0,0) */
void cursorHome() {
	escape2("H");
}

/* Move cursor to specified column and line (x, y) */
void cursorMoveTo(int column, int line) {
	escape(true);
	printf("%i;%iH", line, column);
}

/* Move cursor by the specified amount in the set dir */
void cursorMoveBy(char dir, int amount) {
	escape(true);
	printf("%i%c", amount, dir);
}

/* Gets terminal dimensions from the kernel, works even if terminal window is resized */
void getTerminalSize(int * x, int * y) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    *x = size.ws_col;
    *y = size.ws_row;
}

void cursorHide() {
    escape2("?25l");
}
void cursorShow() {
    escape2("?25h");
}

void screenSave() {
    escape2("?47h");
}
void screenRestore() {
    escape2("?47l");
}