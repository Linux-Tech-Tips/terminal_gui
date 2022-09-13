#include <stdio.h>
#include <string.h>

#include "esc_func.h"

int main() {
    printf("Hello World, program works!\n");
    char * escape = getEscape();
    printf("%s[;31mTHIS TEXT IS RED OMG%s[0m\n", escape, escape);
    return 0;
}