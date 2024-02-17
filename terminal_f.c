#include "terminal_f.h"

/* GLOBAL VARIABLES */

static struct termios oldTerm;


/* TERMINAL FUNCTION IMPLEMENTATIONS */

void modeReset() {
	printf(ESCAPE "0m");
}

void modeSet(int style, int fgColor, int bgColor) {
	printf(ESCAPE);
	/* Printing style code if desired */
	if(style != NO_CODE) printf("%i", style);
	printf(";");
	/* Printing foreground color code if desired (shifting by 10 to account for the code difference) */
	if(fgColor != NO_CODE) printf("%i", (fgColor-10));
	/* Printing background color code if desired */
	if(bgColor != NO_CODE) printf(";%i", bgColor);
	printf("m");
}

void mode256Color(int bg, int colorCode) {
	/* Deciding whether to print a background or foreground 256-color code */
	int mode = bg ? 48 : 38;
	printf(ESCAPE "%i;5;%im", mode, colorCode);
}

void erase() {
	printf(ESCAPE "2J");
}

void eraseLine(int lineType) {
	printf(ESCAPE "%iK", lineType);
}

void cursorHome() {
	printf(ESCAPE "H");
}

void cursorMoveTo(int column, int line) {
	printf(ESCAPE "%i;%iH", line, column);
}

void cursorMoveBy(char dir, int amount) {
	/* Checking if there's any amount to move by, to prevent the escape code from moving the cursor by 1 even if 0 specified */
	if(amount > 0)
		printf(ESCAPE "%i%c", amount, dir);
}

void getTerminalSize(int * x, int * y) {
	struct winsize size;
	/* Getting current terminal size from Kernel call */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	*x = size.ws_col;
	*y = size.ws_row;
}

void startKeys() {
	struct termios newTerm;
	/* Saving current terminal attributes into the oldTerm global structure */
	tcgetattr(STDIN_FILENO, &oldTerm);
	newTerm = oldTerm;
	/* Setting the correct terminal attributes for non-blocking input */
	newTerm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
}

void endKeys() {
	/* Resetting terminal attributes to the ones saved before non-blocking input started */
	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
}

short nbRead(char * buffer, size_t maxToRead) {
	short result = 0;
	struct pollfd fds;
	fds.fd = 1;
	fds.events = POLLIN; /* POLLIN - the type of events the program is looking for - user input */
	/* Using the poll() system function to see if any characters ready to be read in STDIN */
	int ready = poll(&fds, 1, 0);
	char c;
	int r = 0;
	/* Reading from stdin into buffer until no longer ready or EOF reached */
	while(ready > 0 && read(STDIN_FILENO, &c, 1) > 0) {
		result = 1;
		if(r < maxToRead)
			buffer[r] = c;
		ready = poll(&fds, 1, 0);
		++r;
	}
	return result;
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
