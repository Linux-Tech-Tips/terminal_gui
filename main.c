#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "esc_func.h"

int main() {
	erase();
	cursorHome();
    modeSet(STYLE_BOLD, FG_BLACK, BG_CYAN);
	printf(" ");
	cursorMoveBy(DOWN, 1);
    printf("   TEXT IN CYAN BACKGROUND EXAMPLE");
	cursorMoveBy(UP, 1);
	printf(" ");
    modeReset();
	cursorMoveBy(DOWN, 3);
	mode256Color(false, 23);
	printf("MORE TEXT");
	modeReset();
    printf("\n");

    int x = 0;
    int y = 0;
    cursorGetPos(&x, &y);
    printf("test: %i, %i \n", x, y);

    return 0;
}
