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
    char ruch [30] = "cokolwiek";

    wypisz(map, 1, 1);
    reset(token); //wraca czolga do punktu (1,1)
    int x = 0;
    int y = 0;
    Response* response = NULL;

    while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
        fgets(ruch, 30, stdin);
        strcpy(ruch, strtok(ruch, "\n"));

        if(strcmp(ruch, "move") == 0){
            response = move(token);
        }
        else if(strcmp(ruch, "rotate_right") == 0){
            response = rotate(token, "right");
        }
        else if(strcmp(ruch, "rotate_left") == 0){
            response = rotate(token, "left");
        }
        else if(strcmp(ruch, "reset") == 0){
            response = reset(token);
        }
        else if(strcmp(ruch, "info") == 0){
            response = info(token);
        }
        
        //response = info(token); //teraz dzieki tej strukturze Response zapisuje wszystkie dane za jednym wywołaniem funkcji info i nie mam zbędnych stepów
        
        if(strcmp(ruch, "explore") != 0){
            x = response->x;
            y = response->y;
            map->field_type[25-y][x+25] = type(response->field_type);
        }
        else{
            //tutaj zrobic tak zeby uzupelnialo 3 pola przed nami. trzeba tez wyciagnac z tego na jakiej pozycji (x, y) stoimy bo sam explore tego nie zwraca ale wiadomo ze jeden blok przed tym srodkowym z listy
        }

        wypisz(map, x, y); //podswietla na czerwono pozycje na ktorej sie znajdujemy
        printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", response->x, response->y, response->direction, response->step);
    }

    // printf("%s\n", cJSON_Print(info(token, "info")));
    // move(token, "move");
    // printf("%s\n", cJSON_Print(info(token, "info")));
    // rotate(token, "left", "rotate");
    // printf("%s\n", cJSON_Print(info(token, "info")));


    free(map);
    return 0;
}