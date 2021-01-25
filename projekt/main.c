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

    Response* response;
    List* explore;

    if(argc == 3 && strcmp(argv[2], "bot") == 0){
        map = bot(map, token);
        png_map("mapa.png", "tilesn.png", map);
    }
    else{ //czesc interaktywna, do latwiejszego testowania poprawnego dzialania programu. W finalnej wersji jej nie bedzie.
        while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
            fgets(command, 30, stdin);
            strcpy(command, strtok(command, "\n"));

            if(strcmp(command, "reset") == 0)
            {
                free_map(map);
                map = reset_map(map, token);
            }
            else if(strcmp(command, "explore") == 0)
            {
                explore = get_explore(token);
                map = interpret_explore(explore, map);
            }
            else
            {
                response = get_struct(token, command);
                map = interpret_response(response, map);
            }

            print_map(map);
            png_map("mapa.png", "tilesn.png", map);
        }
    }

    free_map(map);
    return 0;
}