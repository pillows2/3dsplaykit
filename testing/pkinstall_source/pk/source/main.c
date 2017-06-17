#include <string.h>
#include <3ds.h>
#include <stdio.h>

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); //Uncomment if using stereoscopic 3D
	consoleInit(GFX_TOP, NULL) //Change this line to consoleInit(GFX_BOTTOM, NULL) if using the bottom screen.
	;printf("Welcome to 3DSPlaykit!\nYou are currently viewing the Emulation section\nSadly, I can't provide roms.\nBut, you can just search Google!\nJune 15, 2017\nPress B to quit!");

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		//Your code goes here

		u32 kDown = hidKeysDown();
		if (kDown & KEY_B)
			break; //Break in order to return to hbmenu

		// Flush and swap frame-buffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}