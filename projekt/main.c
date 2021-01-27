#include "image.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

//kolejnosc tesow: load, response, map, logic, image

int main(int argc, char **argv)
{   
    char *token = argv[1];
    char command [30];

    Map* map = set_map(map, token);
    print_map(map);

    map = bot(map, token);
    png_map("mapa.png", "tilesn.png", map);

    free_map(map);
    return 0;
}