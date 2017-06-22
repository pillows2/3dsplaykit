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
		
		if (screen == 0) {
			moveCursor();
			resetCursor(5, 6);
			
			printf("\x1b[1;12HWelcome to the 3DSPlaykit!\e[K\n");
			printf("\x1b[2;6HUse the DPAD and A to make a selection\e[K\n");
			
			printStatement("Tools", 5);
			printStatement("Misc", 6);
			
			if ((hidKeysDown() & KEY_A) & (cursor == 5)) {
				screen = 1;
				consoleClear();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 6)) {
				screen = 2;
				consoleClear();
			}
			
		} else if (screen == 1) {
		
			printf("\x1b[1;1HTools\e[K\n");
		
			moveCursor();
			resetCursor(5, 6);
			
			printStatement("1. JKSM", 5);
			printStatement("2. FTPD", 6);
			
			if ((hidKeysDown() & KEY_A) & (cursor == 5)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/JKSM/", 0777);
				downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
				
				break;
			} else if ((hidKeysDown() & KEY_A) & (cursor == 6)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/FTPD/", 0777);
				downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
			}
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
			}
			
		} else if (screen == 2) {
			
			printf("\x1b[1;1HPress B\e[K\n");
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
			}
			
		}
		

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}