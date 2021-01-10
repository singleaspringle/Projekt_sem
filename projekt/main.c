#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "cJSON/cJSON.h"

//NAPRAWIC PRZECIEKI PAMIECI!!!!!!!!!!

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    Mapa *map = calloc(1, sizeof(Mapa)); //alokuje 50x50 na mape i wpisuje zera
    map->x = 1;
    map->y = 1;
    char ruch [30];

    wypisz(map);
    Response* response = NULL;
    Lista* explore = NULL;
    Pole* p1 = NULL;
    Pole* p2 = NULL;
    Pole* p3 = NULL;

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
            response = reset(token); //wraca czolga do (1, 1) i zeruje zapisane pola
            free(map);
            Mapa *map = calloc(50*50, sizeof(int)); //alokuje 50x50 na mape i wpisuje zera
        }
        else if(strcmp(ruch, "info") == 0){
            response = info(token);
        }
        else if(strcmp(ruch, "explore") == 0){
            explore = exploruj(token);
        }
        
        if(strcmp(ruch, "explore") != 0){
            map->x = response->x;
            map->y = response->y;
            map->field_type[25-(map->y)][(map->x)+25] = type(response->field_type);
            map->step = response->step;

            wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
            printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, response->direction, map->step);

            
            //clean_response(response);
        }
        else{
            map->step ++;
            p1 = explore->l1; //lewy z przodu
            p2 = explore->l2; //po srodku z przodu
            p3 = explore->l3; //prawy z przodu

            if(p1->x == p2->x){   //wtedy czolg jest ustawiony W albo E. Zaczyna od lewej swojej strony z przodu
                if(p1->y > p2->y){    //wtedy czolg jest ustawiony E
                    map->x = p1->x - 1;
                    map->y = p2->y;
                    map->field_type[25 - p1->y][(map->x + 1) + 25] = type(p1->field_type);
                    map->field_type[25 - p2->y][(map->x + 1) + 25] = type(p2->field_type);
                    map->field_type[25 - p3->y][(map->x + 1) + 25] = type(p3->field_type);
                    
                    wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
                    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, "E", map->step);
                }
                else{   //wtedy czolg jest ustawiony W
                    map->x = p1->x + 1;
                    map->y = p2->y;
                    map->field_type[25 - p1->y][(map->x - 1) + 25] = type(p1->field_type);
                    map->field_type[25 - p2->y][(map->x - 1) + 25] = type(p2->field_type);
                    map->field_type[25 - p3->y][(map->x - 1) + 25] = type(p3->field_type);

                    wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
                    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, "W", map->step);
                }
            }
            else if(p1->y == p2->y){   //wtedy czolg jest ustawiony N albo S bo p1->y = p2->y kiedy jest ustawiony N to z jakiegos powodu explore zaczyna od prawej strony (dziwne)
                if(p1->x > p2->x){ //wtedy czolg jest ustawiony N
                    map->x = p2->x;
                    map->y = p1->y - 1;
                    map->field_type[25 - (map->y + 1)][p1->x + 25] = type(p1->field_type);
                    map->field_type[25 - (map->y + 1)][p2->x + 25] = type(p2->field_type);
                    map->field_type[25 - (map->y + 1)][p3->x + 25] = type(p3->field_type);

                    wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
                    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, "N", map->step);
                }
                else{ //wtedy czolg jest ustawiony S
                    map->x = p2->x;
                    map->y = p1->y + 1;
                    map->field_type[25 - (map->y - 1)][p1->x + 25] = type(p1->field_type);
                    map->field_type[25 - (map->y - 1)][p2->x + 25] = type(p2->field_type);
                    map->field_type[25 - (map->y - 1)][p3->x + 25] = type(p3->field_type);

                    wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
                    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, "S", map->step);
                }
            }
        }
    }

    // printf("%s\n", cJSON_Print(info(token, "info")));
    // move(token, "move");
    // printf("%s\n", cJSON_Print(info(token, "info")));
    // rotate(token, "left", "rotate");
    // printf("%s\n", cJSON_Print(info(token, "info")));


    free(map);
    return 0;
}