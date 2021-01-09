#include <stdio.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

typedef struct _Mapa
{
    int field_type [50][50];
} Mapa;

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

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
Response* info(char *token);
cJSON* move(char *token, char* co);
cJSON* rotate(char *token, char *rotation, char* co);
cJSON* explore(char *token, char* co);
cJSON* reset(char *token, char* co);
void wypisz(Mapa *A);
int type(char* nazwa);
