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
    Mapa *map = calloc(50*50, sizeof(int)); //alokuje 50x50 na mape i wpisuje zera
    char ruch [30];

    wypisz(map);
    reset(token, "reset"); //wraca czolga do punktu (1,1)
    int x = 0;
    int y = 0;
    Response* response;

    for(int i = 0; i < 3; i++){
        fgets(ruch, 30, stdin);

        if(strcmp(ruch, "move") == 0){
            move(token, "move");
        }
        else if(strcmp(ruch, "rotateright") == 0){
            rotate(token, "right", "rotate");
        }
        else if(strcmp(ruch, "rotateleft") == 0){
            rotate(token, "left", "rotate");
        }
        
        response = info(token); //teraz dzieki tej strukturze Response zapisuje wszystkie dane za jednym wywołaniem funkcji info i nie mam zbędnych stepów
        
        x = response->x;
        y = response->y;
        map->field_type[y+23][x+25] = type(response->field_type);

        wypisz(map);
        printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", response->x, response->y, response->direction, response->step);
    }

    // printf("%s\n", cJSON_Print(info(token, "info")));
    // move(token, "move");
    // printf("%s\n", cJSON_Print(info(token, "info")));
    // rotate(token, "left", "rotate");
    // printf("%s\n", cJSON_Print(info(token, "info")));

    return 0;
}