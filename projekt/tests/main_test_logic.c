#include "../logic.h"


int main(int argc, char* argv[]){
    if(argc != 2) abort();
    Map* map;
    char* token = argv[1];

    map = set_map(map, token); //testuje tez get_dx i get_dy oraz offset
    print_map(map);
    free_map(map);
    map = reset_map(map, token);
    print_map(map);

    map = bot(map, token); //testuje też brzeg, add_chunk, interpret_response i intepret_explore

    free_map(map);
    return 0;
}