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

void signalHandle(int sigID) {
	printf("Captured signal %i", sigID);
	run = false;
}

void update() {
	erase();
	int termX, termY;
	getTerminalSize(&termX, &termY);

	time_t now = time(0);

	modeSet(NO_CODE, NO_CODE, BG_RED);
	cursorHome();
	cursorMoveTo(termX/2, termY/2);
	if(now % 2 == 0)
		cursorMoveBy(UP, 1);
	else
		cursorMoveBy(DOWN, 1);
	printf(" ");
	modeReset();
	cursorHome();
	printf("Current time: %i", now);
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

	while(run) {
		update();
		struct timespec t;
		t.tv_nsec = 500,000,000;
		t.tv_sec = 0;
		nanosleep(&t, NULL);
	}

	cursorShow();
	screenRestore();

    return 0;
}
