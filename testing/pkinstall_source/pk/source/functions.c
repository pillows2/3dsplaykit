#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h" 

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

void printStatement(char* name, int place) {

		if(cursor == place) {
			printf("\x1b[%d;0H> %s", place, name);
		} else {
			printf("\x1b[%d;0H  %s", place, name);
		}

}