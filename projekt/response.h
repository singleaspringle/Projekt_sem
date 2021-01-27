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

typedef struct _Field{
    int x, y;
    char* field_type;
} Field;

typedef struct _List {
    char* status;
    Field* l1;
    Field* l2;
    Field* l3; //potrzebne do explore
} List;

List* get_explore(char* token);
Response* get_struct(char* token, char* command);
void free_explore(List* explore);
void free_response(Response* response);

#endif