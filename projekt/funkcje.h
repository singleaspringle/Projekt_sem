#include <stdio.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RED "\x1b[31;1m"
#define ANSI_COLOR_RESET "\x1b[37;1m"
#define ANSI_COLOR_GRASS "\x1b[32;1m"
#define ANSI_COLOR_SAND "\x1b[33;1m"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

typedef struct _Mapa
{
    int field_type [50][50];
    int step, x, y; //current_x i current_y
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

typedef struct _Pole{
    int x, y;
    char *field_type;
} Pole;

typedef struct _Lista {
    Pole* l1;
    Pole* l2;
    Pole* l3; //potrzebne do explore
} Lista;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
Response* info(char *token);
Response* move(char *token);
Response* rotate(char *token, char *rotation);
Lista* exploruj(char *token);
Response* reset(char *token);
void wypisz(Mapa *A);
int type(char* nazwa);
void clean_response (Response *dana);
