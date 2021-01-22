#include "load.h"
#include "logic.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    Map *map = create_map(5, 5);
    interpret_response(get_struct(token, "reset"), map);
    char command [30];

    print_map(map);
    Response* response;
    Lista* explore;

    if(argc == 3){
        if(strcmp(argv[2], "bot") == 0){
            map = bot(map, token);
            print_map(map);
            printf("%s\n", brzeg(map));
        }
    }
    else{
        while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
            fgets(command, 30, stdin);
            strcpy(command, strtok(command, "\n"));

            response = get_struct(token, command);

            if(strcmp(command, "reset") == 0)
            {
                free(map);
                Map *map = create_map(5, 5);
            }

            else if(strcmp(command, "explore") == 0)
            {
                explore = get_explore(token);
            }

            if(strcmp(command, "explore") != 0)
            {
                map = interpret_response(response, map);
            }
            else
            {
                map = interpret_explore(explore, map);
            }

            
            print_map(map);
            printf("%s\n", brzeg(map));
        }
    }



    free(map);
    return 0;
}