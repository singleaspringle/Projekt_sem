#ifndef _LOGIC_H
#define _LOGIC_H
#include "map.h"

int type(char* nazwa);
int get_dx(int xp); //wybiera dx tak, zeby przy uruchomieniu programu czolg znajdywal sie w lokalnym punkcie (2, 2). xp to current_x wziete ze struktury API przy uruchomieniu
int get_dy(int yp); //wybiera dy tak, zeby przy uruchomieniu programu czolg znajdywal sie w lokalnym punkcie (2, 2). yp to current_y wziete ze struktury API przy uruchomieniu
int offsetx(int x, Map* A);
int offsety(int y, Map* A);
int loc_to_globx(int xloc, Map* A);
int loc_to_globy(int yloc, Map* A);
//void seek_explored_field();
Map* seek_wall(Map* A, char* token);
Map* set_map(Map* map, char* token);
Map* reset_map(Map* map, char* token);
Map* seek_left_corner(Map* A, char* token);
Map* bot(Map* A, char* token);
Map* interpret_explore (Lista* explore, Map* map);
Map* interpret_response (Response* response, Map* map);
char* brzeg(Map* A);
Map* add_chunk(Map* A);

#endif