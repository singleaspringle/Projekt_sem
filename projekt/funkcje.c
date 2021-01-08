#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON/cJSON.h"
#include "funkcje.h"

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char *make_request(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adres struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
            return "Błąd!\n";
        else
        {
            return chunk.response;
        }
    }
    
    /* zawsze po sobie sprzątaj */
    free(chunk.response);
    curl_easy_cleanup(curl);
}

cJSON* info(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/");
    strcat(url, token);

    cJSON* info = NULL;
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* name = NULL;
    cJSON* current_x = NULL;
    cJSON* current_y = NULL;
    cJSON* current_session = NULL;
    cJSON* direction = NULL;
    cJSON* step = NULL;
    cJSON* field_type = NULL;
    cJSON* field_bonus = NULL;
    cJSON* element = NULL;

    info = cJSON_Parse(make_request(url));

    if(info == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(info, "status");
    payload = cJSON_GetObjectItemCaseSensitive(info, "payload");

    name = cJSON_GetArrayItem(payload, 0);
    current_x = cJSON_GetArrayItem(payload, 1);
    current_y = cJSON_GetArrayItem(payload, 2);
    current_session = cJSON_GetArrayItem(payload, 3);
    direction = cJSON_GetArrayItem(payload, 4);
    step = cJSON_GetArrayItem(payload, 5);
    field_type = cJSON_GetArrayItem(payload, 6);
    field_bonus = cJSON_GetArrayItem(payload, 7);

    free(url);

    return(field_type); //mozna cokolwiek :) :) :)
}

cJSON* move(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/");
    strcat(url, token);
    
    cJSON *move = NULL;
    move = cJSON_Parse(make_request(url));
    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* name = NULL;
    cJSON* current_x = NULL;
    cJSON* current_y = NULL;
    cJSON* current_session = NULL;
    cJSON* direction = NULL;
    cJSON* step = NULL;
    cJSON* field_type = NULL;
    cJSON* field_bonus = NULL;

    if(move == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(move, "status");
    payload = cJSON_GetObjectItemCaseSensitive(move, "payload");
    name = cJSON_GetObjectItemCaseSensitive(payload, "name");
    current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
    current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
    current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
    direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
    step = cJSON_GetObjectItemCaseSensitive(payload, "step");
    field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
    field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");

    free(url);

    end:
        return move;
}

cJSON* rotate(char *token, char *rotation)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/")+strlen(token)+strlen(rotation)+2)); //+2 na slasha i \0
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/");
    strcat(url, token);
    strcat(url, "/");
    strcat(url, rotation);

    cJSON *rotate = NULL;
    rotate = cJSON_Parse(make_request(url));
    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* name = NULL;
    cJSON* current_x = NULL;
    cJSON* current_y = NULL;
    cJSON* current_session = NULL;
    cJSON* direction = NULL;
    cJSON* step = NULL;
    cJSON* field_type = NULL;
    cJSON* field_bonus = NULL;

    if(rotate == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(rotate, "status");
    payload = cJSON_GetObjectItemCaseSensitive(rotate, "payload");
    name = cJSON_GetObjectItemCaseSensitive(payload, "name");
    current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
    current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
    current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
    direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
    step = cJSON_GetObjectItemCaseSensitive(payload, "step");
    field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
    field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");

    free(url);

    end:
        return rotate;
}

cJSON* explore(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/");
    strcat(url, token);

    cJSON *explore = NULL;
    explore = cJSON_Parse(make_request(url));
    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* list = NULL;
    cJSON* element = NULL;

    if(explore == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(explore, "status");
    payload = cJSON_GetObjectItemCaseSensitive(explore, "payload");
    list = cJSON_GetObjectItemCaseSensitive(payload, "list");
    cJSON_ArrayForEach(element, list){
        cJSON* x = cJSON_GetObjectItemCaseSensitive(element, "x");
        cJSON* y = cJSON_GetObjectItemCaseSensitive(element, "y");
        cJSON* type = cJSON_GetObjectItemCaseSensitive(element, "type");
    }

    free(url);

    end:
        return explore;
}

cJSON* reset(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/");
    strcat(url, token);

    cJSON *reset = NULL;
    reset = cJSON_Parse(make_request(url));
    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* name = NULL;
    cJSON* current_x = NULL;
    cJSON* current_y = NULL;
    cJSON* current_session = NULL;
    cJSON* direction = NULL;
    cJSON* step = NULL;
    cJSON* field_type = NULL;
    cJSON* field_bonus = NULL;

    if(reset == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(reset, "status");
    payload = cJSON_GetObjectItemCaseSensitive(reset, "payload");
    name = cJSON_GetObjectItemCaseSensitive(payload, "name");
    current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
    current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
    current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
    direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
    step = cJSON_GetObjectItemCaseSensitive(payload, "step");
    field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
    field_bonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");

    free(url);

    end:
        return reset;
}
