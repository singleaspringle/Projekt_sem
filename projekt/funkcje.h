#include <stdio.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[37m"

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
Response* move(char *token);
Response* rotate(char *token, char *rotation);
cJSON* explore(char *token, char* co);
Response* reset(char *token);
void wypisz(Mapa *A, int x, int y);
int type(char* nazwa);
