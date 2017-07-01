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
			resetCursor(5, 8);
			
			printf("\x1b[1;12HWelcome to the 3DSPlaykit!\e[K\n");
			printf("\x1b[2;6HUse the DPAD and A to make a selection\e[K\n");
			
			printStatement("Tools", 5);
			printStatement("Games", 6);
			printStatement("Emulators", 7);
			printStatement("Install All (Long Wait)", 8);
			
			if ((hidKeysDown() & KEY_A) & (cursor == 5)) {
				screen = 1;
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 6)) {
				screen = 2;
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 7)) {
				screen = 3;
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 8)) {
				downloadAll();
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
			} else if ((hidKeysDown() & KEY_A) & (cursor == 7)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/FTPD/", 0777);
				downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 8)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/Notepad3DS/", 0777);
				downloadToFile("https://github.com/RMcTn/Notepad3DS/releases/download/v1.1/notepad3DS.3dsx", "/3ds/Notepad3DS/Notepad3DS.3dsx");
				resetScreen();
			} else if ((hidKeysDown() & KEY_A) & (cursor == 9)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/CTRMus/", 0777);
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/ctrmus.3dsx?raw=true", "/3ds/CTRMUS/CTRMUS.3dsx");
				resetScreen();
			}
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
				resetScreen();
			}
			
		} else if (screen == 2) {
			
			if (screen == 2) { //Text fragments occur without this
				printf("\x1b[1;1HGames\e[K\n");
			}
			
			moveCursor();
			resetCursor(5, 9);
			
			printStatement("1. 2048-3D", 5);
			printStatement("2. 3DSPaint", 6);
			printStatement("3. Cookie Collector 3DS", 7);
			printStatement("4. Super Haxagon", 8);
			printStatement("5. Install All", 9);
			
			if ((cursor == 5) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/2048-3D", 0777);
				downloadToFile("https://github.com/MrJPGames/2048-3D/blob/master/2048-3D.3dsx?raw=true", "/3ds/2048-3D/2048-3D.3dsx");
			} else if ((cursor == 6) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/3DSPaint", 0777);
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/3DS_Paint.3dsx?raw=true", "/3ds/3DSPaint/3DSPaint.3DSX");
			} else if ((cursor == 7) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/CookieCollector3DS", 0777);
				downloadToFile("https://github.com/Kaisogen/CookieCollector-3DS-/releases/download/v1.6.0/CookieCollector3DS.3dsx", "/3ds/CookieCollector3DS/CookieCollector3DS.3dsx");
			} else if ((cursor == 8) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/SuperHaxagon/", 0777);
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/SuperHaxagon.3dsx?raw=true", "/3ds/SuperHaxagon/SuperHaxagon.3dsx");
			} else if ((cursor == 9) & (kDown & KEY_A)) {
				mkdir("/3ds/", 0777);
				mkdir("/3ds/2048-3D", 0777);
				mkdir("/3ds/3DSPaint", 0777);
				mkdir("/3ds/CookieCollector3DS", 0777);
				mkdir("/3DS/SuperHaxagon", 0777);
				consoleSelect(&bottomScreen);
				downloadToFile("https://github.com/MrJPGames/2048-3D/blob/master/2048-3D.3dsx?raw=true", "/3ds/2048-3D/2048-3D.3dsx");
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/3DS_Paint.3dsx?raw=true", "/3ds/3DSPaint/3DSPaint.3DSX");
				downloadToFile("https://github.com/Kaisogen/CookieCollector-3DS-/releases/download/v1.6.0/CookieCollector3DS.3dsx", "/3ds/CookieCollector3DS/CookieCollector3DS.3dsx");
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/SuperHaxagon.3dsx?raw=true", "/3ds/SuperHaxagon/SuperHaxagon.3dsx");
				consoleSelect(&topScreen);
			}
			
			
			
			if (hidKeysDown() & KEY_B) {
				screen = 0;
				resetScreen();
			}
			
		} else if (screen == 3) {
			moveCursor();
			resetCursor(5, 6);
			
			printStatement("1. Snes9X", 5);
			printStatement("2. Nestopia", 6);
		
			if (hidKeysDown() & KEY_B) {
				screen = 0;
				resetScreen();
			}
			if (screen == 3) { //Text fragments occur without this
				printf("\x1b[1;1HEmulators\e[K\n");
			}
			
			if ((cursor == 5) & (kDown & KEY_A)) {
				mkdir("/3ds/"
				mkdir("/3ds/SNES9X");
				downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/snes9x_3ds.3dsx?raw=true", "/3ds/SNES9X/SNES9X.3dsx");
				
			} else if ((cursor == 6) & (kDown & KEY_A)) {
				
				
				break;
			}
		
		}
		

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
