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

Map* set_map(Map* map, char* token){
    Response* start = get_struct(token, "info");

    map = create_map(5, 5);
    map->dx = get_dx(start->x);
    map->dy = get_dy(start->y);
    map = interpret_response(start, map);

    return map;
}

Map* reset_map(Map* map, char* token){
    Response* response = get_struct(token, "reset");

    map = create_map(5, 5);
    map->dx = get_dx(response->x);
    map->dy = get_dy(response->y);
    map = interpret_response(response, map);
}

int get_dx(int xp){
    return 3-xp;
}

int get_dy(int yp){
    return 3-yp;
}

int offsetx(int x, Map* A){ //zamienia globalna wspolrzedna x na lokalna
    return x + A->dx - 1;
}

int offsety(int y, Map* A){ //zamienia globalna wspolrzedna y na lokalna
    return (A->r - y) - A->dy;
}

int loc_to_globx(int xloc, Map* A){ //zamienia lokalna wspolrzedna y na globalna
    return xloc + 1 - A->dx;
}

int loc_to_globy(int yloc, Map* A){ //zamienia lokalna wspolrzedna y na globalna
    return A->r - yloc - A->dy;
}

// void seek_explored_field(){ //kiedy znajdzie jedna otoczke to zeby szukal nowego nieodkrytego miejsca
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
    A = turn_right(A, token);

    return A;
}

Map* turn_right(Map* A, char* token){
    A = interpret_response(get_struct(token, "rotate_right"), A);
    A = interpret_explore(get_explore(token), A);
    A->l--;

    return A;
}

Map* continue_forward(Map* A, char* token){
    A = interpret_response(get_struct(token, "move"), A);
    A = interpret_explore(get_explore(token), A);

    return A;
}

Map* take_left_corner(Map* A, char* token){
    A = interpret_response(get_struct(token, "move"), A);
    A = interpret_response(get_struct(token, "rotate_left"), A);
    A = interpret_explore(get_explore(token), A);
    A->l++;

    return A;
}

Map* get_out_of_blind_corner(Map* A, char* token, int x0, int y0){
    while(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A)){
        A = interpret_response(get_struct(token, "move"), A);
        if(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A)){
            A = interpret_response(get_struct(token, "rotate_right"), A);
        }
    }
    A->l = -1;

    return A;
}

Map* seek_left_corner(Map* A, char* token){
    if(strcmp(A->direction, "N") == 0){
        if(A->field_type[A->y - 1][A->x] == 3){ //jezeli przed nim jest sciana
            A = turn_right(A, token);
        }
        else if(A->field_type[A->y - 1][A->x - 1] == 3){ //jezeli idzie dalej wzdluz sciany
            A = continue_forward(A, token);
        }
        else{
            A = take_left_corner(A, token);
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "E") == 0){
        if(A->field_type[A->y][A->x + 1] == 3){
            A = turn_right(A, token);
        }
        else if(A->field_type[A->y - 1][A->x + 1] == 3){
            A = continue_forward(A, token);
        }
        else{
            A = take_left_corner(A, token);
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "S") == 0){
        if(A->field_type[A->y + 1][A->x] == 3){
            A = turn_right(A, token);
        }
        else if(A->field_type[A->y + 1][A->x + 1] == 3){
            A = continue_forward(A, token);
        }
        else{
            A = take_left_corner(A, token);
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "W") == 0){
        if(A->field_type[A->y][A->x - 1] == 3){
            A = turn_right(A, token);
        }
        else if (A->field_type[A->y + 1][A->x - 1] == 3){
            A = continue_forward(A, token);
        }
        else{
            A = take_left_corner(A, token);
        }
        print_map(A);
    }
    return A;
}

Map* explore_border(Map* A, char* token, int x0, int y0){
    do{
        A = seek_left_corner(A, token);
        if(A->l == 4)
            break;
    } while(!(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A)));

    return A;
}

Map* bot(Map* A, char* token){
    int x0, y0;
    while(1){ //jedno przejscie petli to jedna otoczka
        A->l = 0;
        A = seek_wall(A, token);
        x0 = loc_to_globx(A->x, A);                                              
        y0 = loc_to_globy(A->y, A);
        A = get_out_of_blind_corner(A, token, x0, y0); //zeby A->x != x0 i A->y != y0
        A = explore_border(A, token, x0, y0);
        printf("l = %d\n", A->l);

        if(A->l == -4)
            break;
        else
            continue;
    }

    return A;
}

char* edge(Map* A){ //pokazuje przy jakim brzegu jestesmy
    if(A->y == 0){ //przy gornym brzegu
        return "N";
    }
    else if(A->y == A->r - 1){ //przy dolnym brzegu
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
    if (strcmp(edge(A), "N") == 0){
        B = create_map(2*A->r, A->c);
        strcpy(B->direction, A->direction);
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
    if (strcmp(edge(A), "E") == 0){
        B = create_map(A->r, 2*A->c);
        strcpy(B->direction, A->direction);
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
    if (strcmp(edge(A), "S") == 0){
        B = create_map(2*A->r, A->c);
        strcpy(B->direction, A->direction);
        B->step = A->step;
        B->dx = A->dx;
        B->dy = A->dy + A->r;
        B->x = A->x;
        B->y = A->y;
        for(int i = 0; i < A->r; i++){
            for(int j = 0; j < A->c; j++){
                B->field_type[i][j] = A->field_type[i][j];
            }
        }
        free_map(A);
        return B;
    }
    if (strcmp(edge(A), "W") == 0){
        B = create_map(A->r, 2*A->c);
        strcpy(B->direction, A->direction);
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

Map* interpret_explore (List* explore, Map* map){
    int l = map->l;
    Map* new = add_chunk(map);
    new->step++;
    new->l = l;

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

    free_explore(explore);

    return new;
}

Map* interpret_response (Response* response, Map* map){
    int l = map->l;
    Map* new = add_chunk(map);

    new->x = offsetx(response->x, new);
    new->y = offsety(response->y, new);
    new->field_type[new->y][new->x] = type(response->field_type);
    new->step = response->step;
    strcpy(new->direction, response->direction);
    new->l = l;

    free_response(response);
    return new;
}

