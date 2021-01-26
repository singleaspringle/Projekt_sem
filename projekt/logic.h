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
Map* turn_right(Map* A, char* token);
Map* continue_forward(Map* A, char* token);
Map* take_left_corner(Map* A, char* token);
Map* get_out_of_blind_corner(Map* A, char* token, int x0, int y0);
Map* explore_border(Map* A, char* token, int x0, int y0);
Map* set_map(Map* map, char* token);
Map* reset_map(Map* map, char* token);
Map* seek_left_corner(Map* A, char* token);
Map* bot(Map* A, char* token);
Map* interpret_explore (List* explore, Map* map);
Map* interpret_response (Response* response, Map* map);
char* edge(Map* A);
Map* add_chunk(Map* A);

#endif