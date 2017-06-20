#include <string.h>
#include <3ds.h>
#include <stdio.h>
#include <sys/stat.h> 
#include <sys/types.h> 

#include "functions.h"

extern int cursor = 5;
extern int screen = 0;

int main()
{
	httpcInit(0);
	gfxInitDefault();
	PrintConsole topScreen, bottomScreen;
	
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 

		consoleSelect(&topScreen);
		
		
		if (screen == 0) { // Home Screen
		
			moveCursor();
			resetCursor(5, 8);
		
			printf("\x1b[1;12HWelcome to the 3DSPlaykit!\e[K\n");
			printf("\x1b[2;6HUse the DPAD and A to make a selection\e[K\n");
			
			printStatement("Full Install (Long install time)", 5);
			printStatement("Games", 6);
			printStatement("Emulators", 7);
			printStatement("Tools", 8);
		
		
			if((cursor == 5) & (kDown & KEY_A)) {
				screen = 1;
				cursor = 0;
				consoleClear();
			} else if ((cursor = 6) & (kDown & KEY_A)) {
				screen = 2; 
				cursor = 0;
				consoleClear();
			} else if ((cursor = 7) & (kDown & KEY_A)) {
				screen = 3;
				cursor = 0;
				consoleClear();
			} else if ((cursor = 8) & (kDown & KEY_A)) {
				screen = 4;
				cursor = 0;
				consoleClear();
			}
	
		} else if (screen == 1) {
			resetScreen();
			moveCursor();
			resetCursor(0,0);
			printf("\x1b[1;12HEmpty Page Here\e[K\n");
			printf("\x1b[2;12HPress B to go back.\e[K\n");

		} else if (screen == 4) {
			printf("\x1b[1;22Tools\e[K\n");
		
			resetScreen();
			resetCursor(5, 6);
			moveCursor();
			
			printStatement("1. JKSM", 5);
			printStatement("2. FTPD II Turbo", 6);
			
			if ((cursor == 5) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/JKSM/", 0777);
				downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
			} else if ((cursor == 6) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/FTPD", 0777);
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