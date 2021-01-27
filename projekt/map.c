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
    A->direction = calloc(2, sizeof(char));
    A->l = 0;

    return A;
}

Map* load_map(FILE* fin){ //wczytuje z pliku
    char s[2] = "|";
    int r, c;
    char bufor[100];
    char* w;
    int row = 0;
    fscanf(fin, "%s", bufor);
    r = atoi(bufor);
    fscanf(fin, "%s", bufor);
    c = atoi(bufor);
    Map* A = create_map(r, c);
    fgets(bufor, 100, fin);
    for(int i = 0; i < 2*r + 1; i++){
        if(i%2 != 0){
            fgets(bufor, 100, fin); //wczytuje wiersz
            w = strtok(bufor, s); //oddziela numer wiersza od reszty
            for(int j = 0; j < c; j++){
                w = strtok(NULL, s); //wczytuje kolejne komorki z wiersza
                A->field_type[row][j] = w[1] - 48;
            }
            row++;
        }
        else{
            fgets(bufor, 100, fin); //tutaj sczytuje te linijki z +---+---...
        }
    }
    fgets(bufor, strlen(bufor), fin);
    fscanf(fin, "%s", bufor);
    A->x = atoi(bufor);
    fscanf(fin, "%s", bufor);
    A->y = A->r - 1 - atoi(bufor);
    fscanf(fin, "%s", bufor);
    strcpy(A->direction, bufor);
    fscanf(fin, "%s", bufor);
    A->step = atoi(bufor);
    fscanf(fin, "%s", bufor);
    A->dx = atoi(bufor);
    fscanf(fin, "%s", bufor);
    A->dy = atoi(bufor);

    return A;
}

void free_map(Map* A){
    for(int i = 0; i < A->r; i++){
        free(A->field_type[i]);
    }
    free(A->field_type);
    free(A->direction);
    free(A);
}

void print_map(Map *A){
    printf(ANSI_COLOR_RESET);
    for(int i = 0; i < A->r; i++){
        printf("   ");
        for(int j = 0; j < A->c; j++){
            printf("+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        printf("+\n%3d", A->r - 1 - i); //wypisuje numer wiersza
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
            printf("%4d", j); //wypisuje nr kolumny
    }
    printf("\n");
    
    printf("x: %d\ny: %d\ndirection: %s\nstep: %d\n", A->x, A->r - 1 - (A->y), A->direction, A->step);
}

void fprint_map(Map *A, FILE *fout){ //zapisuje do pliku
    fprintf(fout, "%d\n", A->r);
    fprintf(fout, "%d\n", A->c);
    for(int i = 0; i < A->r; i++){
        fprintf(fout, "   ");
        for(int j = 0; j < A->c; j++){
            fprintf(fout, "+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        fprintf(fout, "+\n%3d", A->r - 1 - i); //wypisuje numer wiersza
        for(int j = 0; j < A->c; j++){
            fprintf(fout, "|%2d ", A->field_type[i][j]);
        }
        fprintf(fout, "|\n");
    }
    fprintf(fout, "   ");
    for(int j = 0; j < A->c; j++){
        fprintf(fout, "+---"); //wypisuje rozdzielenie miedzy wierszami
    }
    fprintf(fout, "+\n");
    fprintf(fout, "  ");
    for(int j = 0; j < A->c; j++){
            fprintf(fout, "%4d", j); //wypisuje nr kolumny
    }
    fprintf(fout, "\n");
    
    fprintf(fout, "%d\n%d\n%s\n%d\n%d\n%d\n", A->x, A->r - 1 - (A->y), A->direction, A->step, A->dx, A->dy);
}


