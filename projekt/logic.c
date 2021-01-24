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

void free_explore(Lista* explore){
    free(explore->status);
    free(explore->l1->field_type);
    free(explore->l2->field_type);
    free(explore->l3->field_type);
    free(explore->l1);
    free(explore->l2);
    free(explore->l3);
    free(explore);
}

void free_response(Response* response){
    free(response->field_bonus);
    free(response->field_type);
    free(response->name);
    free(response->session);
    free(response->direction);
    free(response->status);
    free(response);
}

Map* set_map(Map* map, char* token){
    Response* start = get_struct(token, "info");

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
    A = interpret_response(get_struct(token, "rotate_right"), A);
    A = interpret_explore(get_explore(token), A);
    return A;
}

Map* seek_left_corner(Map* A, char* token){
    if(strcmp(A->direction, "N") == 0){
        if(A->field_type[A->y - 1][A->x] == 3){ //jezeli przed nim jest sciana
            A = interpret_response(get_struct(token, "rotate_right"), A);
            A = interpret_explore(get_explore(token), A);
            A->l--;
        }
        else if(A->field_type[A->y - 1][A->x - 1] == 3){
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_explore(get_explore(token), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
            A = interpret_explore(get_explore(token), A);
            A->l++;
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "E") == 0){
        if(A->field_type[A->y][A->x + 1] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
            A = interpret_explore(get_explore(token), A);
            A->l--;
        }
        else if(A->field_type[A->y - 1][A->x + 1] == 3){
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_explore(get_explore(token), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
            A = interpret_explore(get_explore(token), A);
            A->l++;
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "S") == 0){
        if(A->field_type[A->y + 1][A->x] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
            A = interpret_explore(get_explore(token), A);
            A->l--;
        }
        else if(A->field_type[A->y + 1][A->x + 1] == 3){
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_explore(get_explore(token), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
            A = interpret_explore(get_explore(token), A);
            A->l++;
        }
        print_map(A);
    }
    else if(strcmp(A->direction, "W") == 0){
        if(A->field_type[A->y][A->x - 1] == 3){
            A = interpret_response(get_struct(token, "rotate_right"), A);
            A = interpret_explore(get_explore(token), A);
            A->l--;
        }
        else if (A->field_type[A->y + 1][A->x - 1] == 3){
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_explore(get_explore(token), A);
        }
        else{
            A = interpret_response(get_struct(token, "move"), A);
            A = interpret_response(get_struct(token, "rotate_left"), A);
            A = interpret_explore(get_explore(token), A);
            A->l++;
        }
        print_map(A);
    }
    return A;
}

Map* bot(Map* A, char* token){
    int x0, y0;
    A->l = 0;
    //jezeli A->l = 4 to jest wewnetrzna przeszkoda, jezeli A->l = -4 to znaczy ze jest zewnetrzna otoczka
    //for(int i = 0; i < 1; i++){ //tutaj powinno byc cos takiego ze jakby jedno przejscie przez fora to jest jedna otoczka. Kiedy skonczy to zaczyna sie drugie przejscie przez fora i jakos trzeba go skierowac zeby szukal nowej otoczki, albo zaczal wypelniac
        A = seek_wall(A, token);
        x0 = loc_to_globx(A->x, A);     //poniewaz podczas algorytmu seek_left_corner mapa sie rozszerza, to postanowilismy zapisac x0 i y0 we wspolrzednych globalnych                                         
        y0 = loc_to_globy(A->y, A);     //wtedy w warunku while na biezaco sprawdzamy globalne wspolrzedne i nie ma znaczenia rozmiar mapy wzgledem tego co byl na poczatku
        while(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A)){
            A = interpret_response(get_struct(token, "move"), A);
            if(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A))
                A = interpret_response(get_struct(token, "rotate_right"), A);
        }
        do{ //trzeba tutaj zrobic cos takiego, zeby on najpierw wyszedl z tego miejsca gdzie znalazl sciane a pozniej dopiero zapisal x0 i y0 bo jak na przyklad bedzie musial 2 razy sie obrocic to od razu przerwie while bo x = x0 i y = y0
            A = seek_left_corner(A, token);
        } while(!(x0 == loc_to_globx(A->x, A) && y0 == loc_to_globy(A->y, A))); //chodzi o to zeby przerywal algorytm kiedy wroci do miejsca w ktorym zaczal seek_left_corner.
        
        
    //}

    return A;
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
    if (strcmp(brzeg(A), "N") == 0 || strcmp(brzeg(A), "NE") == 0 || strcmp(brzeg(A), "NW") == 0){
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
    if (strcmp(brzeg(A), "E") == 0 || strcmp(brzeg(A), "NE") == 0 || strcmp(brzeg(A), "SE") == 0){
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
    if (strcmp(brzeg(A), "S") == 0 || strcmp(brzeg(A), "SE") == 0 || strcmp(brzeg(A), "SW") == 0){
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
    if (strcmp(brzeg(A), "W") == 0 || strcmp(brzeg(A), "NW") == 0 || strcmp(brzeg(A), "SW") == 0){
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

Map* interpret_explore (Lista* explore, Map* map){
    int l = map->l;
    Map* new = add_chunk(map);
    new->step ++;
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

