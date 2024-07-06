#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include <signal.h>

#include "terminal_f.h"

static volatile bool run = true;

static int pSigID;

static short showDebug = 0;

void signalHandle(int sigID) {
	pSigID = sigID;
	run = false;
}

void update(void) {
	char c [4] = {0};
	short res = nbRead(c, 3);
	if(c[0] == 'q' || c[1] == 'q' || c[2] == 'q') run = false;

	if(c[0] == 'c' || c[1] == 'c' || c[2] == 'c') showDebug = 1;
	if(c[0] == 'v' || c[1] == 'v' || c[2] == 'v') showDebug = 0;

	cursorHome();
	modeReset();
	cursorMoveBy(DOWN, 4);
	if(showDebug) printf("DEBUG");
	else printf("     ");

	int termX, termY;
	getTerminalSize(&termX, &termY);

	time_t now = time(0);

	// Clearing circle in the middle - only clearing what needs to be cleared prevents flicker
	cursorHome();
	cursorMoveTo(termX/2, termY/2);
	modeSet(NO_CODE, COLOR_DEFAULT, COLOR_DEFAULT);
	cursorMoveBy(UP, 1);
	cursorMoveBy(LEFT, 1);
	printf("   ");
	cursorMoveBy(LEFT, 3);
	cursorMoveBy(DOWN, 1);
	printf("   ");
	cursorMoveBy(LEFT, 3);
	cursorMoveBy(DOWN, 1);
	printf("   ");

	// Rendering only the current part of the circle, based on the time
	cursorHome();
	cursorMoveTo(termX/2, termY/2);
	modeSet(NO_CODE, NO_CODE, COLOR_RED);
	switch(now % 8) {
		case 0:
			cursorMoveBy(UP, 1);
			break;
		case 1:
			cursorMoveBy(UP, 1);
			cursorMoveBy(LEFT, 1);
			break;
		case 2:
			cursorMoveBy(LEFT, 1);
			break;
		case 3:
			cursorMoveBy(LEFT, 1);
			cursorMoveBy(DOWN, 1);
			break;
		case 4:
			cursorMoveBy(DOWN, 1);
			break;
		case 5:
			cursorMoveBy(DOWN, 1);
			cursorMoveBy(RIGHT, 1);
			break;
		case 6:
			cursorMoveBy(RIGHT, 1);
			break;
		case 7:
			cursorMoveBy(RIGHT, 1);
			cursorMoveBy(UP, 1);
			break;
	}
	printf(" ");

	// Printing text info
	modeReset();
	cursorHome();
	printf("Current time: %i", (int) now);
	cursorHome();
	cursorMoveBy(DOWN, 1);
	if(res)
		printf("Read character: %s", c);
	else
		printf("Read character:    ");
	fflush(stdout);
}

int main(void) {

	signal(SIGINT, signalHandle);
	fflush(stdout);

	// Simple program for now, works until ctrl+c is pressed

	screenSave();
	erase();
	cursorHide();
	startKeys();

	while(run) {
		update();
		struct timespec t = {0};
		t.tv_nsec = 100000000;
		t.tv_sec = 0;
		nanosleep(&t, NULL);
	}

	cursorShow();
	screenRestore();
	endKeys();

	printf("Program ended with captured signal of id %i\n", pSigID);

    return 0;
}
