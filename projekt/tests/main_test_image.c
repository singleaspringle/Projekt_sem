#include "../image.h"

int main(int argc, char* argv[]){
    FILE *fmap = fopen("mapa.txt", "r+");
    Map* map = load_map(fmap);
    fclose(fmap);

    png_map("tests/mapa.png", "tilesn.png", map);

    free_map(map);
    return 0;
}