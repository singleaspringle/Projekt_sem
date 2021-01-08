#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"
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

    curl_global_init(0);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

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
    curl_global_cleanup();
}

char* info(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/");
    strcat(url, token);

    cJSON *info = cJSON_Parse(make_request(url));
    
    cJSON* status;
    cJSON* payload;
    cJSON* name;
    cJSON* current_x;
    cJSON* current_y;
    cJSON* current_session;
    cJSON* direction;
    cJSON* step;
    cJSON* field_type;
    cJSON* field_bonus;

    if(info == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
        status->valuestring = "Error";
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(info, "status");
    if(cJSON_IsString(status) && (status->valuestring != NULL))
        printf("status: %s\n", status->valuestring);

    
    free(url);

    end:
        cJSON_Delete(info);
        return status->valuestring;
}

char* move(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/");
    strcat(url, token);

    return make_request(url);

    free(url);
}

char* rotate(char *token, char *rotation)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/")+strlen(token)+strlen(rotation)+2)); //+2 na slasha i \0
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/");
    strcat(url, token);
    strcat(url, "/");
    strcat(url, rotation);

    return make_request(url);

    free(url);
}

char* explore(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/");
    strcat(url, token);

    return make_request(url);

    free(url);
}

char* reset(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/");
    strcat(url, token);

    return make_request(url);

    free(url);
}
