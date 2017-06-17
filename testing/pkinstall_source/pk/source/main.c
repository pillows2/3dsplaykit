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
		
		}
		
		
		

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}