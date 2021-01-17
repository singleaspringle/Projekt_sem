#include "load.h"
#include "logika.h"
#include "map.h"
#include "response.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    Map *map = calloc(1, sizeof(Map)); //alokuje 50x50 na mape i wpisuje zera
    map->x = 1;
    map->y = 1;
    char command [30];

    wypisz(map);
    Response* response;
    Lista* explore;

    while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
        fgets(command, 30, stdin);
        strcpy(command, strtok(command, "\n"));

        response = get_struct(token, command);

        if(strcmp(command, "reset") == 0)
        {
            free(map);
            Map *map = calloc(1, sizeof(Map));
        }

        else if(strcmp(command, "explore") == 0)
        {
            explore = get_explore(token);
        }
        
        if(strcmp(command, "explore") != 0)
        {
            map->x = response->x;
            map->y = response->y;
            map->field_type[25-(map->y)][(map->x)+25] = type(response->field_type);
            map->step = response->step;
            map->direction = response->direction;
        }
        else
        {
            interpret_explore(explore, map);
        }

        

        wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
        printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, map->direction, map->step);
    }

    // printf("%s\n", cJSON_Print(info(token, "info")));
    // move(token, "move");
    // printf("%s\n", cJSON_Print(info(token, "info")));
    // rotate(token, "left", "rotate");
    // printf("%s\n", cJSON_Print(info(token, "info")));


    free(map);
    return 0;
}