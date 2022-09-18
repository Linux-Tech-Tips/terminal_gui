#ifndef ESC_FUNC_H
#define ESC_FUNC_H

/* Unique code constant declarations */
extern const int NO_CODE;
// FG COLORS
extern const int FG_BLACK;
extern const int FG_RED;
extern const int FG_GREEN;
extern const int FG_YELLOW;
extern const int FG_BLUE;
extern const int FG_MAGENTA;
extern const int FG_CYAN;
extern const int FG_WHITE;
extern const int FG_DEFAULT;
// BG COLORS
extern const int BG_BLACK;
extern const int BG_RED;
extern const int BG_GREEN;
extern const int BG_YELLOW;
extern const int BG_BLUE;
extern const int BG_MAGENTA;
extern const int BG_CYAN;
extern const int BG_WHITE;
extern const int BG_DEFAULT;
// STYLES
extern const int STYLE_BOLD;
extern const int STYLE_FAINT;
extern const int STYLE_ITALIC;
extern const int STYLE_UNDERLINE;
extern const int STYLE_BLINKING;
extern const int STYLE_REVERSE;
extern const int STYLE_HIDDEN;
extern const int STYLE_STRIKETHROUGH;
// DIRECTIONS
extern const char UP;
extern const char DOWN;
extern const char LEFT;
extern const char RIGHT;
// LINE ERASE TYPES
extern const int LINE_TO_END;
extern const int LINE_FROM_START;
extern const int LINE_ALL;

// TERMINAL FUNCTIONS

/* Prints out the escape character into the console */
void escape(bool withBracket);

/* Prints out an escape sequence, starting with the escape character, then an open bracket, followed with the input text */
void escape2(char * text);

/* Resets all modes (styles and colors) */
void modeReset();

/* Sets the mode */
void modeSet(int style, int fgColor, int bgColor);

/* Sets a 256 color mode */
void mode256Color(bool bg, int colorCode);

/* Erases the screen */
void erase();

/* Erases on the current line, according to the specified variable */
void eraseLine(int lineType);

/* Move cursor to home position (0,0) */
void cursorHome();

/* Move cursor to specified column and line (x, y) */
void cursorMoveTo(int column, int line);

/* Move cursor by the specified amount in the set dir */
void cursorMoveBy(char dir, int amount);

/* Gets terminal dimensions from the kernel, works even if terminal window is resized */
void getTerminalSize(int * x, int * y);

void cursorHide();
void cursorShow();

void screenSave();
void screenRestore();

#endif
