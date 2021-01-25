#include "../map.h"

int main(int argc, char* argv[]){
    Map* map;

    FILE *fin = fopen("mapa.txt", "r+");
    map = load_map(fin); //testuje tez create_map
    print_map(map);
    fclose(fin);

    FILE *fout = fopen("tests/mapa_wypisz.txt", "w+");
    fprint_map(map, fout);
    fclose(fout);

    free_map(map);

    return 0;
}