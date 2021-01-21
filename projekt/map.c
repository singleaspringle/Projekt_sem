#include "map.h"

Map* create_map(int r, int c){
    Map *A = calloc(1, sizeof(Map));
    A->r = r;
    A->c = c;
    A->field_type = (int**) calloc(A->r, sizeof(int*));
    for(int i = 0; i < A->r; i++){
        A->field_type[i] = (int*) calloc(A->c, sizeof(int));
    }
    A->dx = 2;
    A->dy = 2;
    A->x = 2;
    A->y = 2;
    A->step = 0;
    A->direction = NULL;

    return A;
}

void free_map(Map* A){
    for(int i = 0; i < A->r; i++){
        free(A->field_type[i]);
    }
    free(A);
}

void print_map(Map *A){
    printf(ANSI_COLOR_RESET);
    for(int i = A->r - 1; i >= 0; i--){
        printf("   ");
        for(int j = 0; j < A->c; j++){
            printf("+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        printf("+\n%3d", i + 1); //wypisuje numer wiersza
        for(int j = 0; j < A->c; j++){
            if(A->y == i && A->x == j){ //podswietla na cyanowo nasza pozycje aktualna
                printf("|");
                printf(ANSI_COLOR_CYAN);
                printf("%2d ", A->field_type[i][j]);
                printf(ANSI_COLOR_RESET);
            }
            else if(A->field_type[i][j] == 1){
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
        printf("|\n");
    }
    printf("   ");
    for(int j = 0; j < A->c; j++){
        printf("+---"); //wypisuje rozdzielenie miedzy wierszami
    }
    printf("+\n");
    printf("  ");
    for(int j = 0; j < A->c; j++){
            printf("%4d", j+1); //wypisuje nr kolumny
    }
    printf("\n");
    
    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", (A->x)+1, (A->y)+1, A->direction, A->step);
}


