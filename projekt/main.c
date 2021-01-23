#include "load.h"
#include "logic.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    char command [30];
    Map *map = create_map(5, 5);

    Response* start;
    start = get_struct(token, "info");

    map->dx = get_dx(start->x);
    map->dy = get_dy(start->y);
    map = interpret_response(start, map);

    print_map(map);
    //printf("%s\n", brzeg(map));

    Response* response;
    Lista* explore;

    if(argc == 3){
        if(strcmp(argv[2], "bot") == 0){
            map = bot(map, token);
            print_map(map);
            //printf("%s\n", brzeg(map));
        }
    }
    else{
        while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
            fgets(command, 30, stdin);
            strcpy(command, strtok(command, "\n"));

            if(strcmp(command, "reset") == 0)
            {
                response = get_struct(token, command);
                //free(map);
                map = create_map(5, 5);
                map->dx = get_dx(response->x);
                map->dy = get_dy(response->y);
                map = interpret_response(response, map);
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
            //printf("%s\n", brzeg(map));
        }
    }

    free(map);
    return 0;
}