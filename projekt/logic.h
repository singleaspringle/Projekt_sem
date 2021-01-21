#ifndef _LOGIC_H
#define _LOGIC_H
#include "load.h"

int type(char* nazwa);
Map* interpret_explore (Lista* explore, Map* map);
Map* interpret_response (Response* response, Map* map);
int offsetx(int x, Map* A);
int offsety(int y, Map* A);
char* brzeg(Map* A);
Map* add_chunk(Map* A);

#endif