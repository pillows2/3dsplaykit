#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

extern int cursor;
extern int screen;

void moveCursor();
void resetCursor(int min, int max);
void printStatement(char* name, int place);

#endif