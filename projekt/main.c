#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"
#include "cJSON/cJSON.h"

int main(int argc, char **argv)
{   
    char *token = argv[1];
    cJSON* wynik = NULL;
    for(int i = 2; i < argc; i++){
        if(strcmp(argv[i], "info") == 0)
            wynik = info(token);
        else if(strcmp(argv[i], "move") == 0)
        {
            wynik = move(token);
        }
        else if(strcmp(argv[i], "rotate") == 0)
        {
            wynik = rotate(token, argv[i + 1]);
            i++; //dlatego ze rotate ma jeszcze informacje, w ktora strone
        }
        else if(strcmp(argv[i], "explore") == 0)
        {
            wynik = explore(token);
        }
        else if(strcmp(argv[i], "reset") == 0)
        {
            wynik = reset(token); //cofa do 1,1 ale kierunek pozostaje
        }
        else
        {
            printf("Nie ma takiej komendy\n");
        }
        if(wynik != NULL)
            cJSON_Print(wynik);   
    }

    return 0;
}