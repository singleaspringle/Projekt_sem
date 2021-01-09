#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "cJSON/cJSON.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    Mapa *map = calloc(50*50, sizeof(int));
    char ruch [32];

    wypisz(map);
    reset(token, "reset");
    int x = 0;
    int y = 0;
    for(int i = 0; i < 5; i++){
        fgets(ruch, 32, stdin);
        if(strcmp(ruch, "rotate left") == 0){
            rotate(token, "left", "rotate");
        }
        else if(strcmp(ruch, "rotate right") == 0){
            rotate(token, "right", "rotate");
        }
        else if(strcmp(ruch, "move") == 0){
            move(token, "move");
        }
        x = atoi(cJSON_Print(info(token, "x")));
        y = atoi(cJSON_Print(info(token, "y")));
        map->field_type[y+23][x+25] = type(cJSON_Print(info(token, "type")));
        wypisz(map);
        
        printf("%s\n", cJSON_Print(info(token, "info")));
    }
    

    return 0;
}