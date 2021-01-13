#ifndef _LIST_H
#define _LIST_H
#include "load.h"

typedef struct _Pole{
    int x, y;
    char *field_type;
} Pole;

typedef struct _Lista {
    Pole* l1;
    Pole* l2;
    Pole* l3; //potrzebne do explore
} Lista;

Lista* exploruj(char *token);
int type(char* nazwa);


#endif