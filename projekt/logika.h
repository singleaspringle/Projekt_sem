#ifndef _LIST_H
#define _LIST_H
#include "load.h"
#include "map.h"
#include "response.h"

int type(char* nazwa);
void interpret_explore (Lista* explore, Map* map);
void interpret_response (Response* response, Map* map);
int offsetx(int x, Map* A);
int offsety(int y, Map* A);
char* brzeg(Map* A);

#endif