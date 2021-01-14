#ifndef _MAP_H
#define _MAP_H
#include "load.h"

typedef struct _Mapa
{
    int field_type [50][50];
    int step, x, y; //current_x i current_y
    char* direction;
    int dx, dy;
} Mapa;

void wypisz(Mapa *A);

#endif