#include "logika.h"

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
    return y + A->dy - 1;
}

void interpret_explore (Lista* explore, Map* map){
    map->step ++;

    if(strcmp(map->direction, "E") == 0){
        map->x = offsetx(explore->l1->x - 1, map);
        map->y = offsety(explore->l2->y, map);
        map->field_type[map->y + 1][map->x + 1] = type(explore->l1->field_type);
        map->field_type[map->y][map->x + 1] = type(explore->l2->field_type);
        map->field_type[map->y - 1][map->x + 1] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "W") == 0){
        map->x = offsetx(explore->l1->x + 1, map);
        map->y = offsety(explore->l2->y, map);
        map->field_type[map->y - 1][map->x - 1] = type(explore->l1->field_type);
        map->field_type[map->y][map->x - 1] = type(explore->l2->field_type);
        map->field_type[map->y + 1][map->x - 1] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "N") == 0){
        map->x = offsetx(explore->l2->x, map);
        map->y = offsety(explore->l1->y - 1, map);
        map->field_type[map->y + 1][map->x + 1] = type(explore->l1->field_type);
        map->field_type[map->y + 1][map->x] = type(explore->l2->field_type);
        map->field_type[map->y + 1][map->x - 1] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "S") == 0){
        map->x = offsetx(explore->l2->x, map);
        map->y = offsety(explore->l1->y + 1, map);
        map->field_type[map->y - 1][map->x - 1] = type(explore->l1->field_type);
        map->field_type[map->y - 1][map->x] = type(explore->l2->field_type);
        map->field_type[map->y - 1][map->x + 1] = type(explore->l3->field_type);
    }
}

void interpret_response (Response* response, Map* map){
    map->x = offsetx(response->x, map);
    map->y = offsety(response->y, map);
    map->field_type[map->y][map->x] = type(response->field_type);
    map->step = response->step;
    map->direction = response->direction;
}

char* brzeg(Map* A){ //pokazuje przy jakim brzegu jestesmy
    if(A->y == A->r - 1){ //przy gornym brzegu
        if(A->x == A->c - 1) //gorny prawy
            return "NE";
        else if(A->x == 0) //gorny lewy
            return "NW";
        else //gorny
            return "N";
    }
    else if(A->y == 0){ //przy dolnym brzegu
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
        return "(null)";
}