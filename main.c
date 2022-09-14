#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "esc_func.h"

int main() {
    modeSet(STYLE_BOLD, FG_BLACK, BG_CYAN);
    printf("\n\n   TEXT IN CYAN BACKGROUND EXAMPLE\n");
    modeReset();
    printf("\n");
    return 0;
}
