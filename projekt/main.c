#include "load.h"

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
    Response* response;
    Lista* explore = NULL;
    Pole* p1 = NULL;
    Pole* p2 = NULL;
    Pole* p3 = NULL;

    while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
        fgets(ruch, 30, stdin);
        strcpy(ruch, strtok(ruch, "\n"));

        response = get_struct(token, ruch);

        if(strcmp(ruch, "reset") == 0){
            free(map);
            Mapa *map = calloc(1, sizeof(Mapa));
        }

        else if(strcmp(ruch, "explore") == 0){
            explore = exploruj(token);
        }
        
        if(strcmp(ruch, "explore") != 0){
            map->x = response->x;
            map->y = response->y;
            map->field_type[25-(map->y)][(map->x)+25] = type(response->field_type);
            map->step = response->step;
            map->direction = response->direction;

            wypisz(map); //podswietla na czerwono pozycje na ktorej sie znajdujemy
            printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", map->x, map->y, map->direction, map->step);

            
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