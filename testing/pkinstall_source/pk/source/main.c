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
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 6)) {
				screen = 2;
				resetScreen();
			}
			
		} else if (screen == 1) {
		
			printf("\x1b[1;1HTools\e[K\n");
		
			moveCursor();
			resetCursor(5, 9);
			
			printStatement("1. Full Install", 5);
			printStatement("2. JKSM", 6);
			printStatement("3. FTPD", 7);
			printStatement("4. Notepad3DS", 8);
			printStatement("5. CTRMUS", 9);
			
			if ((hidKeysDown() & KEY_A) & (cursor == 5)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/JKSM/", 0777);
				mkdir("/3ds/FTPD/", 0777);
				mkdir("/3ds/Notepad3DS", 0777);
				mkdir("/3ds/CTRMus", 0777);
				consoleSelect(&bottomScreen);
				downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
				downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
				downloadToFile("https://github.com/RMcTn/Notepad3DS/releases/download/v1.1/notepad3DS.3dsx", "/3ds/Notepad3DS/Notepad3DS.3dsx");
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/ctrmus.3dsx?raw=true", "/3ds/CTRMUS/CTRMUS.3dsx");

				resetScreen();
				consoleSelect(&topScreen);
			
			} else if ((hidKeysDown() & KEY_A) & (cursor == 6)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/JKSM/", 0777);
				downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
				resetScreen();
				break;
			} else if ((hidKeysDown() & KEY_A) & (cursor == 7)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/FTPD/", 0777);
				downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
				resetScreen();
				break;
			} else if ((hidKeysDown() & KEY_A) & (cursor == 8)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/Notepad3DS/", 0777);
				downloadToFile("https://github.com/RMcTn/Notepad3DS/releases/download/v1.1/notepad3DS.3dsx", "/3ds/Notepad3DS/Notepad3DS.3dsx");
				resetScreen();
				break;
			} else if ((hidKeysDown() & KEY_A) & (cursor == 9)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/CTRMus/", 0777);
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/ctrmus.3dsx?raw=true", "/3ds/CTRMUS/CTRMUS.3dsx");
				resetScreen();
				break;
			}
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
				resetScreen();
			}
			
		} else if (screen == 2) {
			
			if (screen == 2) { //Text fragments occur without this
				printf("\x1b[1;1HPress B\e[K\n");
			}
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
				resetScreen();
			}
			
		}
		

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}