#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include "functions.h"

extern int cursor = 0;
extern int screen = 0;

int main()
{
	gfxInitDefault();
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Your code goes here

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; //Break in order to return to hbmenu

		//Select Screens
	
		//Choose which screen to print to (top)
		consoleSelect(&topScreen);
		
		moveCursor();
		resetCursor(5, 8);
		
		if (screen == 0) { // Home Screen
		
			printf("\x1b[1;12HWelcome to the 3DSPlaykit!\e[K\n");
			printf("\x1b[2;6HUse the DPAD and A to make a selection\e[K\n");
			
			printStatement("Full Install (Long install time)", 5);
			printStatement("Games", 6);
			printStatement("Emulators", 7);
			printStatement("Tools", 8);
		
		
			if((cursor == 5) & (kDown & KEY_A)) {
				screen = 1;
				cursor = 0;
			} else if ((cursor = 6) & (kDown & KEY_A)) {
				screen = 2; 
				cursor = 0;
			} else if ((cursor = 7) & (kDown & KEY_A)) {
				screen = 3;
				cursor = 0;
			} else if ((cursor = 8) & (kDown & KEY_A)) {
				screen = 4;
				cursor = 0;
			}
			
		} else if (screen == 1) {
			printf("Incomplete, will not work. Unfunctional.");
		} else if (screen == 2) {
			printf("Incomplete, will not work.");
		} else if (screen == 3) {
			printf("Incomplete, will not work.");
		} else if (screen == 4) {
			printf("\x1b[1;22Tools\e[K\n");
		
			resetCursor(5, 6);
			moveCursor();
			
			printStatement("1. JKSM", 5);
			printStatement("2. FTPD II Turbo", 6);
			
			if ((cursor == 5) & (kDown & KEY_A)) {
				downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
			} else if ((cursor == 6) & (kDown & KEY_A)) {
				downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
			}
		
		}
		
		
		

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}