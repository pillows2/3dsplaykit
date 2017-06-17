#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <sys/stat.h> 
#include <sys/types.h> 
void moveCursor() {

	if (hidKeysDown() & KEY_DOWN) {
		cursor++;
	} else if (hidKeysDown() & KEY_UP) {
		cursor--;
	}
}

void resetCursor(int min, int max) {
	if (cursor > max) {
		cursor = max;
	} else if (cursor < min) {
		cursor = min;
	}
}

void printStatement(char* name, u64 cost, int place) {

	if (cursor == place) {
		printf("\x1b[%d;2H\x1b[40;33m>\x1b[0m %s: %llu \e[K\n")(, Install all apps, 3);
	} else {
		printf("\x1b[%d;2H  %s: %llu \e[K\n")(, Install games, 6;
	}

}