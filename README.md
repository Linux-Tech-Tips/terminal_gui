# terminal_gui

An example project in which it is attempted to remake basic functionality of the ncurses library using pure C, with ANSI escape codes for cursor and style control.

UNIX only, because the UNIX C standard library unistd.h is used.

ANSI Escape sequence reference is [available here](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797).

## Branch details

The 'main' branch contains only the header file and C implementation file, so that this repo can be cloned into projects using it as a module.

To see a practical example of the header in use, check out the 'demo' branch, with a *main.c* with a short demonstration program, and a Makefile to build the executable.

## Usage guidelines

All function declarations include comments describing the usage and functionality.

A few guidelines on how to use this header:
- Use *modeSet()* and *modeReset()* to set terminal drawing style
- Use *erase()* and *eraseLine()* to clear certain parts of the terminal
- Use *cursorHome()*, *cursorMoveTo()* and *cursorMoveBy()* to move the cursor within the terminal
- Use *getTerminalSize()* to get the current size of the terminal (NOTE: recommended check frequently in case window resized)
- Use *cursorHide()* and *cursorShow()* to change the visibility of the cursor
- Use *screenSave()* and *screenRestore()* to save the terminal state before program execution and restore it after program termination
- Use *nbRead()* to read characters from STDIN without blocking the terminal and waiting for the user to press enter
  - before using *nbRead()*, set the current terminal properties using *startKeys()*
  - after using *nbRead()*, before program termination, restore the previous terminal properties using *endKeys()*
