#ifndef _MAP_H
#define _MAP_H
#include "load.h"

typedef struct _Map
{
    int r, c;
    int **field_type;
    int step, x, y; //lokalne x i y
    char* direction;
    int dx, dy;
} Map;

void print_map(Map *A);
Map* create_map(int r, int c);
void powieksz_mape(Map* A);

#endif