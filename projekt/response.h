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


Response* reset(char *token);
Response* info(char *token);
Response* move(char *token);
Response* rotate(char *token, char *rotation);
void clean_response (Response *dana);

#endif