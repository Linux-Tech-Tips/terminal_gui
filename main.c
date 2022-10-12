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
	char c = getchar(); // TODO Fix, blocks until character is read
	erase();
	int termX, termY;
	getTerminalSize(&termX, &termY);

	time_t now = time(0);

	modeSet(NO_CODE, NO_CODE, BG_RED);
	cursorHome();
	cursorMoveTo(termX/2, termY/2);
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
	cursorMoveBy(RIGHT, 1);
	/*if(now % 2 == 0)
		cursorMoveBy(UP, 1);
	else
		cursorMoveBy(DOWN, 1);*/
	printf(" ");
	modeReset();
	cursorHome();
	printf("Current time: %i", now);
	cursorHome();
	cursorMoveBy(DOWN, 1);
	printf("Read character: %c", c);
	fflush(stdout);
}

int main() {

	signal(SIGINT, signalHandle);
	fflush(stdout);

	// Simple program for now, works until ctrl+c is pressed
	// TODO Next implement catching keyboard logs

	screenSave();
	erase();
	cursorHide();
	startKeys();

	while(run) {
		update();
		struct timespec t;
		//t.tv_nsec = 500,000,000;
		//t.tv_sec = 0;
		//nanosleep(&t, NULL);
		sleep(1);
	}

	cursorShow();
	screenRestore();
	endKeys();

	printf("Program ended with captured signal of id %i\n", pSigID);

    return 0;
}
