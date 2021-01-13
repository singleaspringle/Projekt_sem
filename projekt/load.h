#ifndef _load_H
#define _load_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON/cJSON.h"
#include "response.h"
#include "list.h"
#include "map.h"

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

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);


#endif

