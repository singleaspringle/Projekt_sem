#ifndef _MAP_H
#define _MAP_H
#include "response.h"

typedef struct _Map
{
    int r, c;
    int **field_type;
    int step, x, y; //lokalne x i y
    char* direction;
    int dx, dy;
    int l;
} Map;

void free_map(Map* A);
Map* load_map(FILE* fin);
void print_map(Map *A);
void fprint_map(Map *A, FILE *fout);
Map* create_map(int r, int c);

#endif