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

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
cJSON* info(char *token, char* co);
cJSON* move(char *token, char* co);
cJSON* rotate(char *token, char *rotation, char* co);
cJSON* explore(char *token, char* co);
cJSON* reset(char *token, char* co);
void wypisz(Mapa *A);
int type(char* nazwa);
