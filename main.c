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

void signalHandle(int sigID) {
	pSigID = sigID;
	run = false;
}

void update() {
	//char * c = (char *) malloc(3 * sizeof(char));
	char c [4];
	short res = nbRead(c, 3);
	c[3] = '\0';
	if(*c == 'q') run = false;
	//erase();
	int termX, termY;
	getTerminalSize(&termX, &termY);

	time_t now = time(0);

	// Clearing circle in the middle - only clearing what needs to be cleared prevents flicker
	cursorHome();
	cursorMoveTo(termX/2, termY/2);
	modeSet(NO_CODE, FG_DEFAULT, BG_DEFAULT);
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
	modeSet(NO_CODE, NO_CODE, BG_RED);
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

int main() {

	signal(SIGINT, signalHandle);
	fflush(stdout);

	// Simple program for now, works until ctrl+c is pressed

	screenSave();
	erase();
	cursorHide();
	startKeys();

	while(run) {
		update();
		struct timespec t;
		t.tv_nsec = 500,000,000;
		t.tv_sec = 0;
		nanosleep(&t, NULL);
		//sleep(1);
	}

	cursorShow();
	screenRestore();
	endKeys();

	printf("Program ended with captured signal of id %i\n", pSigID);

    return 0;
}
