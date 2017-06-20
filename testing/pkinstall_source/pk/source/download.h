#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <3ds.h>

int downloadToFile(const char * url, const char * filepath);
int setupContext(httpcContext * context, const char * url, u32 * size);
#endif