#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    return 0;
}
