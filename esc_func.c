#include <stdio.h>
#include <stdbool.h>

#include "esc_func.h"

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


/* Prints out the escape character into the console */
void escape(bool withBracket) {
    printf("\x1b");
    if(withBracket) printf("[");
}

/* Resets all modes (styles and colors) */
void modeReset() {
    escape(true);
    printf("0m");
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
	escape(true);
	printf("2J");
}

/* Move cursor to home position (0,0) */
void cursorHome() {
	escape(true);
	printf("H");
}

/* Move cursor to specified line and column */
void cursorMoveTo(int line, int column) {
	escape(true);
	printf("%i;%iH", line, column);
}

/* Move cursor by the specified amount in the set dir */
void cursorMoveBy(char dir, int amount) {
	escape(true);
	printf("%i%c", amount, dir);
}


