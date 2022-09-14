#include <stdio.h>
#include <string.h>

#include "esc_func.h"

int main() {
    printf("Program start\n");
	char red [10];
	strncpy(red, getEscape(), strlen(red));
	strcat(red, "[;31m");
	char reset [10];
	strncpy(reset, getEscape(), strlen(reset));
	strcat(reset, "[0m");
    printf("%sTHIS TEXT IS RED OMG%s\n", red, reset);
	printf("Program end\n");
    return 0;
}
