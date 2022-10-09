#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // UNIX std library - not multiplatform
#include <sys/ioctl.h>

#include "terminal_f.h"

// TERMINAL FUNCTIONS

/* Resets all modes (styles and colors) */
void modeReset() {
    printf(ESCAPE "0m");
}

/* Sets the mode */
void modeSet(int style, int fgColor, int bgColor) {
    printf(ESCAPE);
    if(style != NO_CODE) printf("%i", style);
    printf(";");
    if(fgColor != NO_CODE) printf("%i", fgColor);
    if(bgColor != NO_CODE) printf(";%i", bgColor);
    printf("m");
}

/* Sets a 256 color mode */
void mode256Color(bool bg, int colorCode) {
	int mode = bg ? 48 : 38;
	printf(ESCAPE "%i;5;%im", mode, colorCode);
}

/* Erases the screen */
void erase() {
	printf(ESCAPE "2J");
}

/* Erases on the current line, according to the specified variable */
void eraseLine(int lineType) {
    printf(ESCAPE "%iK", lineType);
}

/* Move cursor to home position (0,0) */
void cursorHome() {
	printf(ESCAPE "H");
}

/* Move cursor to specified column and line (x, y) */
void cursorMoveTo(int column, int line) {
	printf(ESCAPE "%i;%iH", line, column);
}

/* Move cursor by the specified amount in the set dir */
void cursorMoveBy(char dir, int amount) {
	printf(ESCAPE "%i%c", amount, dir);
}

/* Gets terminal dimensions from the kernel, works even if terminal window is resized */
void getTerminalSize(int * x, int * y) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    *x = size.ws_col;
    *y = size.ws_row;
}

void cursorHide() {
    printf(ESCAPE "?25l");
}
void cursorShow() {
    printf(ESCAPE "?25h");
}

void screenSave() {
    printf(ESCAPE "?47h");
}
void screenRestore() {
    printf(ESCAPE "?47l");
}