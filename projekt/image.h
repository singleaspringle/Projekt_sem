#ifndef _IMAGE_H
#define _IMAGE_H
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include "logic.h"

void read_png_file(char *filename, int *width, int *height, 
     png_byte *color_type,  
     png_byte *bit_depth, png_bytep **row_pointers);

void write_png_file(char *filename, int width, int height, 
     png_byte color_type,  
     png_byte bit_depth, png_bytep *row_pointers);

void process_png_file(int width, int height, png_bytep *row_pointers);
void init_png_file(int width, int height, png_bytep *row_pointers);
void copy_tile(int xs, int ys, int width, int height, png_bytep *row_pointers, png_bytep *row_pointers_from, int idx);
int tile_number(int x);
void png_map(char* fout, char* fin, Map* A);
void free_row_pointers(png_bytep *row_pointers, int height);

#endif