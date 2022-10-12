// Test file to show how poll() syscall is used
#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>


static struct termios oldTerm;

/* Sets terminal options for unbuffered read */
void startKeys() {
	struct termios newTerm;
	tcgetattr(STDIN_FILENO, &oldTerm);
	newTerm = oldTerm;
	newTerm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
}

/* Resets terminal options */
void endKeys() {
	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
}

char nbRead() {
	fflush(stdin);
	struct pollfd fds;
	fds.fd = 1;
	fds.events = POLLIN;
	int ready = poll(&fds, 1, 0);
	char c = 0;
	if(ready > 0) {
		c = getchar();
	} // TODO Use something else to get whole line or full stdin content
	return c;
}

int main() {
	startKeys();
	printf("Program start \n");
	while(1) {
		char c = nbRead();
		if(c != 0) {
			if(c == 'q') break;
			printf("Read: %c\n", c);
		} else {
			printf("Read zero only\n");
		}
		fflush(stdout);
		sleep(1);
	}
	endKeys();
}
