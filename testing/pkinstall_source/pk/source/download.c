#include "download.h"
#include "functions.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setupContext(httpcContext * context, const char * url, u32 * size)
{
	Result ret = 0;
	u32 statuscode = 0;
	ret = httpcOpenContext(context, HTTPC_METHOD_GET, url, 1);
	if (ret != 0) {
		printf("Error in:\nhttpcOpenContext\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "User-Agent", "MultiUpdater");
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcSetSSLOpt(context, SSLCOPT_DisableVerify);
	if (ret != 0) {
		printf("Error in:\nhttpcSetSSLOpt\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "Connection", "Keep-Alive");
	if (ret != 0) {
		printf("Error in:\nhttpcAddRequestHeaderField\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcBeginRequest(context);
	if (ret != 0) {
		printf("Error in:\nhttpcBeginRequest\n");
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcGetResponseStatusCode(context, &statuscode);
	if (ret != 0) {
		printf("Error in:\nhttpcGetResponseStatusCode\n");
		httpcCloseContext(context);
		return ret;
	}
	
	if ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308)) {
		char * newurl = malloc(0x1000); // One 4K page for new URL
		if (newurl == NULL) {
			httpcCloseContext(context);
			return 2;
		}
		
		ret = httpcGetResponseHeader(context, "Location", newurl, 0x1000);
		if (ret != 0) {
			printf("Error in:\nhttpcGetResponseHeader\n");
			httpcCloseContext(context);
			free(newurl);
			return ret;
		}
		
		httpcCloseContext(context); // Close this context before we try the next
		
		if (newurl[0] == '/') { //if the url starts with a slash, it's local
			int slashpos = 0;
			char * domainname = strdup(url);
			if (strncmp("http", domainname, 4) == 0) slashpos = 8; //if the url in the entry starts with http:// or https:// we need to skip that
			slashpos = strchr(domainname+slashpos, '/')-domainname;
			domainname[slashpos] = '\0'; // replace the slash with a nullbyte to cut the url
			char * copyurl = strdup(newurl);
			sprintf(newurl, "%s%s", domainname, copyurl);
			free(copyurl);
			free(domainname);
		}
		
		ret = setupContext(context, newurl, size);
		free(newurl);
		return ret;
	}
	
	if (statuscode != 200) {
		printf("Error: HTTP status code is not 200 OK.\nStatus code: %lu\n", statuscode);
		httpcCloseContext(context);
		return 3;
	}
	
	ret = httpcGetDownloadSizeState(context, NULL, size);
	if (ret != 0) {
		printf("Error in:\nhttpcGetDownloadSizeState\n");
		httpcCloseContext(context);
		return ret;
	}
	
	return 0;
}

int downloadToFile(const char * url, const char * filepath)
{
	if (url == NULL) {
		return 1;
	}
	
	if (filepath == NULL) {
		return 1;
	}
	
	httpcContext context;
	Result ret = 0;
	u32 contentsize = 0, readsize = 0;
	
	ret = setupContext(&context, url, &contentsize);
	if (ret != 0) return ret;
	
	
	FILE * fh = fopen(filepath, "wb");
	if (fh == NULL) {
		printf("Error: couldn't open file to write.\n");
		return 5;
	}
	
	u8 * buf = malloc(0x1000);
	if (buf == NULL) {
		httpcCloseContext(&context);
		return 3;
	}
	
	u64 startTime = osGetTime();
	do {
		ret = httpcDownloadData(&context, buf, 0x1000, &readsize);
		fwrite(buf, 1, readsize, fh);
	} while (ret == (Result)HTTPC_RESULTCODE_DOWNLOADPENDING);
	
	free(buf);
	fclose(fh);
	httpcCloseContext(&context);
	
	if (ret != 0) {
		printf("Error in:\nhttpcDownloadData\n");
		return ret;
	}
	
	resetScreen();
	
	return 0;
	
}

void downloadAll () {
	mkdir("/3ds/", 0777);
	
	//Tools	
	mkdir("/3ds/JKSM/", 0777);
	mkdir("/3ds/FTPD/", 0777);
	mkdir("/3ds/Notepad3DS", 0777);
	mkdir("/3ds/CTRMus", 0777);
	consoleSelect(&bottomScreen);
	downloadToFile("https://github.com/J-D-K/JKSM/blob/master/JKSM.3dsx?raw=true", "/3ds/JKSM/JKSM.3dsx");
	downloadToFile("https://github.com/mtheall/ftpd/releases/download/v2.2/ftpd.3dsx", "/3ds/FTPD/FTPD.3dsx");
	downloadToFile("https://github.com/RMcTn/Notepad3DS/releases/download/v1.1/notepad3DS.3dsx", "/3ds/Notepad3DS/Notepad3DS.3dsx");
	downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/ctrmus.3dsx?raw=true", "/3ds/CTRMUS/CTRMUS.3dsx");

	//Games
	mkdir("/3ds/2048-3D", 0777);
	mkdir("/3ds/3DSPaint", 0777);
	mkdir("/3ds/CookieCollector3DS", 0777);
	mkdir("/3DS/SuperHaxagon", 0777);
	consoleSelect(&bottomScreen);
	downloadToFile("https://github.com/MrJPGames/2048-3D/blob/master/2048-3D.3dsx?raw=true", "/3ds/2048-3D/2048-3D.3dsx");
	downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/3DS_Paint.3dsx?raw=true", "/3ds/3DSPaint/3DSPaint.3DSX");
	downloadToFile("https://github.com/Kaisogen/CookieCollector-3DS-/releases/download/v1.6.0/CookieCollector3DS.3dsx", "/3ds/CookieCollector3DS/CookieCollector3DS.3dsx");
	downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/SuperHaxagon.3dsx?raw=true", "/3ds/SuperHaxagon/SuperHaxagon.3dsx");
				
	//Emulators
	mkdir("/3ds/SNES9X");
	downloadToFile("https://github.com/pillows2/pkinstall/blob/master/download/snes9x_3ds.3dsx?raw=true", "/3ds/SNES9X/SNES9X.3dsx");
				
	
}
