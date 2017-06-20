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

void resetScreen() {

	if (kDown & KEY_B) {

	screen = 0;
	
	printf("\x1b[1;0H                       ");
	printf("\x1b[2;0H                       ");
	printf("\x1b[3;0H                       ");
	printf("\x1b[4;0H                       ");
	printf("\x1b[5;0H                       ");
	printf("\x1b[6;0H                       ");
	printf("\x1b[7;0H                       ");
	printf("\x1b[8;0H                       ");
	printf("\x1b[9;0H                       ");

	}

}