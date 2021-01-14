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

void clean_response (Response *dana);
Response* get_struct(char* token, char *command);

#endif