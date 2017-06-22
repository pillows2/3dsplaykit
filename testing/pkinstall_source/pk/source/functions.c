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
	if (cursor < min) {
		cursor = min;
	} else if (cursor > max) {
		cursor = max;
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

	printf("\x1b[0;0H                                                ");
	printf("\x1b[1;0H                                                ");
	printf("\x1b[2;0H                                                ");
	printf("\x1b[3;0H                                                ");
	printf("\x1b[4;0H                                                ");
	printf("\x1b[5;0H                                                ");
	printf("\x1b[6;0H                                                ");
	printf("\x1b[7;0H                                                ");
	printf("\x1b[8;0H                                                ");
	printf("\x1b[9;0H                                                ");
	printf("\x1b[10;0H                                                ");
	printf("\x1b[11;0H                                                ");
	printf("\x1b[12;0H                                                ");
	printf("\x1b[13;0H                                                ");
	printf("\x1b[14;0H                                                ");
	printf("\x1b[15;0H                                                ");
	printf("\x1b[16;0H                                                ");
	printf("\x1b[17;0H                                                ");
	printf("\x1b[18;0H                                                ");
	printf("\x1b[19;0H                                                ");
	printf("\x1b[20;0H                                                ");
	printf("\x1b[21;0H                                                ");
	printf("\x1b[22;0H                                                ");
	printf("\x1b[23;0H                                                ");
	printf("\x1b[24;0H                                                ");
	printf("\x1b[25;0H                                                ");
	printf("\x1b[26;0H                                                ");
	printf("\x1b[27;0H                                                ");

}