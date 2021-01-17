#ifndef _RESPONSE_H
#define _RESPONSE_H
#include "load.h"

typedef struct _Response{
    char* status;
    char* name;
    int x, y;
    char* session;
    char* direction;
    int step;
    char* field_type;
    char* field_bonus;
} Response;

typedef struct _Pole{
    int x, y;
    char *field_type;
} Pole;

typedef struct _Lista {
    char* status;
    Pole* l1;
    Pole* l2;
    Pole* l3; //potrzebne do explore
} Lista;

Lista* get_explore(char *token);
void clean_response (Response *dana);
Response* get_struct(char* token, char *command);

#endif