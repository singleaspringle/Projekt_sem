#ifndef _LOGIC_H
#define _LOGIC_H
#include "load.h"

int type(char* nazwa);
//void seek_explored_field();
void seek_wall(Map* A, char* token);
int seek_left_corner(Map* A, char* token);
void bot(Map* A, char* token);
Map* interpret_explore (Lista* explore, Map* map);
Map* interpret_response (Response* response, Map* map);
int offsetx(int x, Map* A);
int offsety(int y, Map* A);
char* brzeg(Map* A);
Map* add_chunk(Map* A);

#endif