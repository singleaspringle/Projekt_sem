#include "map.h"

void wypisz(Map *A){
    printf(ANSI_COLOR_RESET);
    printf("  ");
    for(int j = 0; j < 50; j++){
            printf("%4d", j-25); //wypisuje nr kolumny
    }
    printf("\n");
    for(int i = 0; i < 50; i++){
        printf("   ");
        for(int j = 0; j < 50; j++){
            printf("+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        printf("+\n%3d", 25-i); //wypisuje numer wiersza
        for(int j = 0; j < 50; j++){
            if(25 - (A->y) == i && (A->x) + 25 == j){
                printf("|");
                printf(ANSI_COLOR_CYAN);
                printf("%2d ", A->field_type[i][j]);
                printf(ANSI_COLOR_RESET);
            }
            else
            {
                if(A->field_type[i][j] == 1){
                    printf("|");
                    printf(ANSI_COLOR_GRASS);
                    printf("%2d ", A->field_type[i][j]);
                    printf(ANSI_COLOR_RESET);
                }
                else if(A->field_type[i][j] == 2){
                    printf("|");
                    printf(ANSI_COLOR_SAND);
                    printf("%2d ", A->field_type[i][j]);
                    printf(ANSI_COLOR_RESET);
                }
                else if(A->field_type[i][j] == 3){
                    printf("|");
                    printf(ANSI_COLOR_RED);
                    printf("%2d ", A->field_type[i][j]);
                    printf(ANSI_COLOR_RESET);
                }
                else{
                    printf("|%2d ", A->field_type[i][j]);
                }
            }
            
        }
        printf("|\n");
    }
    printf("  ");
    for(int j = 0; j < 50; j++){
        printf("+---"); //wypisuje rozdzielenie miedzy wierszami
    }
    printf("+\n\n");
}