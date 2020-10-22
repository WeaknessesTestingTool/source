#include <stdio.h>

void printWrapper(char *string) {
	printf(string);
}

int principal(int argc, char **argv) {
	char buf[5012];
	memcpy(buf, argv[1], 5012);
	printWrapper(argv[1]);
	return (0);
}