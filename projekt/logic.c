#include "logic.h"

int type(char* nazwa){
    if(strcmp(nazwa, "grass") == 0){
        return 1;
    }
    else if(strcmp(nazwa, "sand") == 0){
        return 2;
    }
    else if(strcmp(nazwa, "wall") == 0){
        return 3;
    }
    else return -1;
}

int offsetx(int x, Map* A){ //zamienia globalna wspolrzedna x na lokalna
    return x + A->dx - 1;
}

int offsety(int y, Map* A){ //zamienia globalna wspolrzedna y na lokalna
    return (A->r - y) - A->dx;
}

char* brzeg(Map* A){ //pokazuje przy jakim brzegu jestesmy
    if(A->y == 0){ //przy gornym brzegu
        if(A->x == A->c - 1) //gorny prawy
            return "NE";
        else if(A->x == 0) //gorny lewy
            return "NW";
        else //gorny
            return "N";
    }
    else if(A->y == A->r - 1){ //przy dolnym brzegu
        if(A->x == A->c - 1) //dolny prawy
            return "SE";
        else if(A->x == 0) //dolny lewy
            return "SW";
        else //dolny
            return "S";    
    }
    else if(A->x == A->c - 1) //prawy
        return "E";
    else if(A->x == 0) //lewy
        return "W";
    else
        return "null";
}

Map* add_chunk(Map* A){
    Map* B = NULL;
    if (strcmp(brzeg(A), "N") == 0){
        B = create_map(2*A->r, A->c);
        B->direction = A->direction;
        B->step = A->step;
        B->x = A->x;
        B->y = A->y;
        B->dx = A->dx;
        B->dy = A->dy;
        for(int i = A->r; i < B->r; i++){
            for(int j = 0; j < A->c; j++){
                B->field_type[i][j] = A->field_type[i - A->r][j];
            }
        }
        free_map(A);
    }
    else if (strcmp(brzeg(A), "E") == 0){
        B = create_map(A->r, 2*A->c);
        B->direction = A->direction;
        B->step = A->step;
        B->x = A->x;
        B->y = A->y;
        B->dx = A->dx;
        B->dy = A->dy;
        for(int i = 0; i < A->r; i++){
            for(int j = 0; j < A->c; j++){
                B->field_type[i][j] = A->field_type[i][j];
            }
        }
        free_map(A);
    }
    else if (strcmp(brzeg(A), "S") == 0){
        B = create_map(2*A->r, A->c);
        B->direction = A->direction;
        B->step = A->step;
        B->dx = A->dx;
        B->dy = A->dy + A->r;
        B->x = A->x;
        B->y = A->y + A->r;
        for(int i = 0; i < A->r; i++){
            for(int j = 0; j < A->c; j++){
                B->field_type[i][j] = A->field_type[i][j];
            }
        }
        free_map(A);
    }
    else if (strcmp(brzeg(A), "W") == 0){
        B = create_map(A->r, 2*A->c);
        B->direction = A->direction;
        B->step = A->step;
        B->dx = A->dx + A->c;
        B->dy = A->dy;
        B->x = A->x + A->c;
        B->y = A->y;
        for(int i = 0; i < A->r; i++){
            for(int j = A->c; j < B->c; j++){
                B->field_type[i][j] = A->field_type[i][j-A->c];
            }
        }
        free_map(A);
    }
    else{
        return A;
    }
    
    return B;
}

Map* interpret_explore (Lista* explore, Map* map){
    Map* new = add_chunk(map);
    new->step ++;

    if(strcmp(new->direction, "E") == 0){
        new->x = offsetx(explore->l1->x - 1, new);
        new->y = offsety(explore->l2->y, new);
        new->field_type[new->y + 1][new->x + 1] = type(explore->l1->field_type);
        new->field_type[new->y][new->x + 1] = type(explore->l2->field_type);
        new->field_type[new->y - 1][new->x + 1] = type(explore->l3->field_type);
    }
    else if (strcmp(new->direction, "W") == 0){
        new->x = offsetx(explore->l1->x + 1, new);
        new->y = offsety(explore->l2->y, new);
        new->field_type[new->y - 1][new->x - 1] = type(explore->l1->field_type);
        new->field_type[new->y][new->x - 1] = type(explore->l2->field_type);
        new->field_type[new->y + 1][new->x - 1] = type(explore->l3->field_type);
    }
    else if (strcmp(new->direction, "N") == 0){
        new->x = offsetx(explore->l2->x, new);
        new->y = offsety(explore->l1->y - 1, new);
        new->field_type[new->y - 1][new->x + 1] = type(explore->l1->field_type);
        new->field_type[new->y - 1][new->x] = type(explore->l2->field_type);
        new->field_type[new->y - 1][new->x - 1] = type(explore->l3->field_type);
    }
    else if (strcmp(new->direction, "S") == 0){
        new->x = offsetx(explore->l2->x, new);
        new->y = offsety(explore->l1->y + 1, new);
        new->field_type[new->y + 1][new->x - 1] = type(explore->l1->field_type);
        new->field_type[new->y + 1][new->x] = type(explore->l2->field_type);
        new->field_type[new->y + 1][new->x + 1] = type(explore->l3->field_type);
    }

    return new;
}

Map* interpret_response (Response* response, Map* map){
    Map* new = add_chunk(map);

    new->x = offsetx(response->x, new);
    new->y = offsety(response->y, new);
    new->field_type[new->y][new->x] = type(response->field_type);
    new->step = response->step;
    new->direction = response->direction;

    return new;
}

