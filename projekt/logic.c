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

// void seek_explored_field(){
//     ;
// }

Map* seek_wall(Map* A, char* token){
    int prevx = -1;
    int prevy = -1;
    while(!(prevx == A->x && prevy == A->y)){ //idzie do przodu dopoki napotka sciane
        prevx = A->x;
        prevy = A->y;
        A = interpret_response(get_struct(token, "move"), A);
        print_map(A);
    }
    A = interpret_response(get_struct(token, "rotate_right"), A);
    print_map(A);

    return A;
}

Map* seek_left_corner(Map* A, char* token){
    A = interpret_explore(get_explore(token), A);

    if(strcmp(A->direction, "N") == 0){
        while(A->field_type[A->y - 1][A->x - 1] == 3){ //lewy z przodu
            if(A->field_type[A->y - 1][A->x] == 3){ //jezeli przed nim jest sciana
                break;
            }
            else{
                A = interpret_response(get_struct(token, "move"), A);
                A = interpret_explore(get_explore(token), A);
            }
            print_map(A);
        }

        if(A->field_type[A->y - 1][A->x] == 3){ //jezeli przed nim jest sciana to
            A = interpret_response(get_struct(token, "rotate_right"), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
        }
    }
    if(strcmp(A->direction, "E") == 0){
        while(A->field_type[A->y - 1][A->x + 1] == 3){
            if(A->field_type[A->y][A->x + 1] == 3){
                break;
            }
            else{
                A = interpret_response(get_struct(token, "move"), A);
                A = interpret_explore(get_explore(token), A);
            }
            print_map(A);
        }

        if(A->field_type[A->y][A->x + 1] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
        }
    }
    if(strcmp(A->direction, "S") == 0){
        while(A->field_type[A->y + 1][A->x + 1] == 3){
            if(A->field_type[A->y + 1][A->x] == 3){
                break;
            }
            else{
                A = interpret_response(get_struct(token, "move"), A);
                A = interpret_explore(get_explore(token), A);
            }
            print_map(A);
        }

        if(A->field_type[A->y + 1][A->x] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
        }
    }
    if(strcmp(A->direction, "W") == 0){
        while(A->field_type[A->y + 1][A->x - 1] == 3){
            if(A->field_type[A->y][A->x - 1] == 3){
                break;
            }
            else{
                A = interpret_response(get_struct(token, "move"), A);
                A = interpret_explore(get_explore(token), A);
            }
            print_map(A);
        }
        
        if(A->field_type[A->y][A->x - 1] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
        }
    }
    return A;
}

Map* bot(Map* A, char* token){
    int x0, y0;
    int l; //jezeli l = 4 to jest wewnetrzna przeszkoda, jezeli l = -4 to znaczy ze jest zewnetrzna otoczka
    //for(int i = 0; i < 1; i++){ //tutaj powinno byc cos takiego ze jakby jedno przejscie przez fora to jest jedna otoczka. Kiedy skonczy to zaczyna sie drugie przejscie przez fora i jakos trzeba go skierowac zeby szukal nowej otoczki, albo zaczal wypelniac
        l = 0;
        A = seek_wall(A, token);
        printf("wall found\n"); //zaczyna obchodzenie otoczki, juz jest skierowany rownolegle do sciany
        x0 = A->x;                                              //trzeba tu pomyslec jak to zrobic, bo chcemy zeby on robil seek corner dopoki nie wroci w to samo miejsce
        y0 = A->y;                                              //ale jezeli stoi pod sciana to od razu jest w tym samym miejscu i wtedy jest glupio
        while(x0 == A->x && y0 == A->y){
            A = interpret_response(get_struct(token, "move"), A);
            if(A->x == x0 && A->y == y0)
                A = interpret_response(get_struct(token, "rotate_right"), A); 
        }
        printf("looking for left corner\n");
        while(!(x0 == A->x && y0 == A->y)){
            A = seek_left_corner(A, token);
            printf("left corner found\n");
        }
        // if(l == 4){
        //     //wypelnij
        // }
    //}

    return A;
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
        return B;
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
        return B;
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
        return B;
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
        return B;
    }
    else{
        return A;
    }
}

Map* interpret_explore (Lista* explore, Map* map){
    Map* new = add_chunk(map);
    new->step ++;

    if(strcmp(new->direction, "E") == 0){
        new->x = offsetx(explore->l1->x - 1, new);
        new->y = offsety(explore->l2->y, new);
        new->field_type[new->y - 1][new->x + 1] = type(explore->l1->field_type);
        new->field_type[new->y][new->x + 1] = type(explore->l2->field_type);
        new->field_type[new->y + 1][new->x + 1] = type(explore->l3->field_type);
    }
    else if (strcmp(new->direction, "W") == 0){
        new->x = offsetx(explore->l1->x + 1, new);
        new->y = offsety(explore->l2->y, new);
        new->field_type[new->y + 1][new->x - 1] = type(explore->l1->field_type);
        new->field_type[new->y][new->x - 1] = type(explore->l2->field_type);
        new->field_type[new->y - 1][new->x - 1] = type(explore->l3->field_type);
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

    free(explore->l1);
    free(explore->l2);
    free(explore->l3);
    free(explore);

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

