#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"

int main(int argc, char **argv)
{   
    char *token = argv[1];
    for(int i = 2; i < argc; i++){
        if(strcmp(argv[i], "info") == 0)
            printf("%s\n", info(token));
        // else if(strcmp(argv[i], "move") == 0)
        // {
        //     printf("%s\n", move(token));
        // }
        // else if(strcmp(argv[i], "rotate") == 0)
        // {
        //     printf("%s\n", rotate(token, argv[i+1]));
        //     i++;
        // }
        // else if(strcmp(argv[i], "explore") == 0)
        // {
        //     printf("%s\n", explore(token));
        // }
        // else if(strcmp(argv[i], "reset") == 0)
        // {
        //     printf("%s\n", reset(token)); //cofa do 1,1 ale kierunek pozostaje
        // }
        // else
        // {
        //     printf("Nie ma takiej komendy\n");
        // }    
    }

    return 0;
}