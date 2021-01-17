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

void interpret_explore (Lista* explore, Map* map){
    map->step ++;

    if(strcmp(map->direction, "E") == 0){
        map->x = explore->l1->x - 1;
        map->y = explore->l2->y;
        map->field_type[25 - explore->l1->y][(map->x + 1) + 25] = type(explore->l1->field_type);
        map->field_type[25 - explore->l2->y][(map->x + 1) + 25] = type(explore->l2->field_type);
        map->field_type[25 - explore->l3->y][(map->x + 1) + 25] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "W") == 0){
        map->x = explore->l1->x + 1;
        map->y = explore->l2->y;
        map->field_type[25 - explore->l1->y][(map->x - 1) + 25] = type(explore->l1->field_type);
        map->field_type[25 - explore->l2->y][(map->x - 1) + 25] = type(explore->l2->field_type);
        map->field_type[25 - explore->l3->y][(map->x - 1) + 25] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "N") == 0){
        map->x = explore->l2->x;
        map->y = explore->l1->y - 1;
        map->field_type[25 - (map->y + 1)][explore->l1->x + 25] = type(explore->l1->field_type);
        map->field_type[25 - (map->y + 1)][explore->l2->x + 25] = type(explore->l2->field_type);
        map->field_type[25 - (map->y + 1)][explore->l3->x + 25] = type(explore->l3->field_type);
    }
    else if (strcmp(map->direction, "S") == 0){
        map->x = explore->l2->x;
        map->y = explore->l1->y + 1;
        map->field_type[25 - (map->y - 1)][explore->l1->x + 25] = type(explore->l1->field_type);
        map->field_type[25 - (map->y - 1)][explore->l2->x + 25] = type(explore->l2->field_type);
        map->field_type[25 - (map->y - 1)][explore->l3->x + 25] = type(explore->l3->field_type);
    }
}