#include <stdio.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
cJSON* info(char *token);
cJSON* move(char *token);
cJSON* rotate(char *token, char *rotation);
cJSON* explore(char *token);
cJSON* reset(char *token);
