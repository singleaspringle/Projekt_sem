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

Response* info(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/");
    strcat(url, token);

    Response* wynik = calloc(1, sizeof(Response));
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
    wynik->status = malloc(sizeof(char)*(strlen(cJSON_Print(status)) + 1));
    strcpy(wynik->status, cJSON_Print(status));

    payload = cJSON_GetObjectItemCaseSensitive(info, "payload");

    name = cJSON_GetArrayItem(payload, 0);
    wynik->name = malloc(sizeof(char)*(strlen(cJSON_Print(name)) + 1));
    strcpy(wynik->name, cJSON_Print(name));

    current_x = cJSON_GetArrayItem(payload, 1);
    wynik->x = atoi(cJSON_Print(current_x));

    current_y = cJSON_GetArrayItem(payload, 2);
    wynik->y = atoi(cJSON_Print(current_y));

    current_session = cJSON_GetArrayItem(payload, 3);
    wynik->session = malloc(sizeof(char)*(strlen(cJSON_Print(current_session)) + 1));
    strcpy(wynik->session, cJSON_Print(current_session));

    direction = cJSON_GetArrayItem(payload, 4);
    wynik->direction = malloc(sizeof(char)*(strlen(cJSON_Print(direction)) + 1));
    strcpy(wynik->direction, cJSON_Print(direction));

    step = cJSON_GetArrayItem(payload, 5);
    wynik->step = atoi(cJSON_Print(step));

    field_type = cJSON_GetArrayItem(payload, 6);
    wynik->field_type = malloc(sizeof(char)*(strlen(cJSON_Print(field_type)) + 1));
    strcpy(wynik->field_type, cJSON_Print(field_type));

    field_bonus = cJSON_GetArrayItem(payload, 7);
    wynik->field_bonus = malloc(sizeof(char)*(strlen(cJSON_Print(field_bonus)) + 1));
    strcpy(wynik->field_bonus, cJSON_Print(field_bonus));

    free(url);
    return wynik;
}

Response* move(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/");
    strcat(url, token);
    
    Response* wynik = calloc(1, sizeof(Response));
    cJSON* move = NULL;
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

    move = cJSON_Parse(make_request(url));

    if(move == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(move, "status");
    wynik->status = malloc(sizeof(char)*(strlen(cJSON_Print(status)) + 1));
    strcpy(wynik->status, cJSON_Print(status));

    payload = cJSON_GetObjectItemCaseSensitive(move, "payload");

    name = cJSON_GetArrayItem(payload, 0);
    wynik->name = malloc(sizeof(char)*(strlen(cJSON_Print(name)) + 1));
    strcpy(wynik->name, cJSON_Print(name));

    current_x = cJSON_GetArrayItem(payload, 1);
    wynik->x = atoi(cJSON_Print(current_x));

    current_y = cJSON_GetArrayItem(payload, 2);
    wynik->y = atoi(cJSON_Print(current_y));

    current_session = cJSON_GetArrayItem(payload, 3);
    wynik->session = malloc(sizeof(char)*(strlen(cJSON_Print(current_session)) + 1));
    strcpy(wynik->session, cJSON_Print(current_session));

    direction = cJSON_GetArrayItem(payload, 4);
    wynik->direction = malloc(sizeof(char)*(strlen(cJSON_Print(direction)) + 1));
    strcpy(wynik->direction, cJSON_Print(direction));

    step = cJSON_GetArrayItem(payload, 5);
    wynik->step = atoi(cJSON_Print(step));

    field_type = cJSON_GetArrayItem(payload, 6);
    wynik->field_type = malloc(sizeof(char)*(strlen(cJSON_Print(field_type)) + 1));
    strcpy(wynik->field_type, cJSON_Print(field_type));

    field_bonus = cJSON_GetArrayItem(payload, 7);
    wynik->field_bonus = malloc(sizeof(char)*(strlen(cJSON_Print(field_bonus)) + 1));
    strcpy(wynik->field_bonus, cJSON_Print(field_bonus));

    free(url);
    return wynik;
}

Response* rotate(char *token, char *rotation)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/")+strlen(token)+strlen(rotation)+2)); //+2 na slasha i \0
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/");
    strcat(url, token);
    strcat(url, "/");
    strcat(url, rotation);

    Response* wynik = calloc(1, sizeof(Response));
    cJSON* rotate = NULL;    
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

    rotate = cJSON_Parse(make_request(url));

    if(rotate == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(rotate, "status");
    wynik->status = malloc(sizeof(char)*(strlen(cJSON_Print(status)) + 1));
    strcpy(wynik->status, cJSON_Print(status));

    payload = cJSON_GetObjectItemCaseSensitive(rotate, "payload");

    name = cJSON_GetArrayItem(payload, 0);
    wynik->name = malloc(sizeof(char)*(strlen(cJSON_Print(name)) + 1));
    strcpy(wynik->name, cJSON_Print(name));

    current_x = cJSON_GetArrayItem(payload, 1);
    wynik->x = atoi(cJSON_Print(current_x));

    current_y = cJSON_GetArrayItem(payload, 2);
    wynik->y = atoi(cJSON_Print(current_y));

    current_session = cJSON_GetArrayItem(payload, 3);
    wynik->session = malloc(sizeof(char)*(strlen(cJSON_Print(current_session)) + 1));
    strcpy(wynik->session, cJSON_Print(current_session));

    direction = cJSON_GetArrayItem(payload, 4);
    wynik->direction = malloc(sizeof(char)*(strlen(cJSON_Print(direction)) + 1));
    strcpy(wynik->direction, cJSON_Print(direction));

    step = cJSON_GetArrayItem(payload, 5);
    wynik->step = atoi(cJSON_Print(step));

    field_type = cJSON_GetArrayItem(payload, 6);
    wynik->field_type = malloc(sizeof(char)*(strlen(cJSON_Print(field_type)) + 1));
    strcpy(wynik->field_type, cJSON_Print(field_type));

    field_bonus = cJSON_GetArrayItem(payload, 7);
    wynik->field_bonus = malloc(sizeof(char)*(strlen(cJSON_Print(field_bonus)) + 1));
    strcpy(wynik->field_bonus, cJSON_Print(field_bonus));

    free(url);
    return wynik;
}

Lista* exploruj(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/");
    strcat(url, token);

    cJSON* explore = NULL;    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* list = NULL;
    cJSON* element = NULL;
    cJSON* x = NULL;
    cJSON* y = NULL;
    cJSON* type = NULL;
    cJSON* list1 = NULL;
    cJSON* list2 = NULL;
    cJSON* list3 = NULL;
    Lista* wynik = (Lista*) malloc(sizeof(Lista));
    wynik->l1 = (Pole*) malloc(sizeof(Pole));
    wynik->l2 = (Pole*) malloc(sizeof(Pole));
    wynik->l3 = (Pole*) malloc(sizeof(Pole));
    
    explore = cJSON_Parse(make_request(url));

    if(explore == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(explore, "status");
    payload = cJSON_GetObjectItemCaseSensitive(explore, "payload");

    list = cJSON_GetArrayItem(payload, 0);

    list1 = cJSON_GetArrayItem(list, 0);
    wynik->l1->x = atoi(cJSON_Print(list1->child));
    wynik->l1->y = atoi(cJSON_Print(list1->child->next));
    wynik->l1->field_type = cJSON_Print(list1->child->next->next);
    
    list2 = cJSON_GetArrayItem(list, 1); 
    wynik->l2->x = atoi(cJSON_Print(list2->child));
    wynik->l2->y = atoi(cJSON_Print(list2->child->next));
    wynik->l2->field_type = cJSON_Print(list2->child->next->next);

    list3 = cJSON_GetArrayItem(list, 2);
    wynik->l3->x = atoi(cJSON_Print(list3->child));
    wynik->l3->y = atoi(cJSON_Print(list3->child->next));
    wynik->l3->field_type = cJSON_Print(list3->child->next->next);

    free(url);
    return wynik;
}

Response* reset(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/");
    strcat(url, token);

    Response* wynik = calloc(1, sizeof(Response));
    cJSON* reset = NULL;    
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
    
    reset = cJSON_Parse(make_request(url));

    if(reset == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    status = cJSON_GetObjectItemCaseSensitive(reset, "status");
    wynik->status = malloc(sizeof(char)*(strlen(cJSON_Print(status)) + 1));
    strcpy(wynik->status, cJSON_Print(status));

    payload = cJSON_GetObjectItemCaseSensitive(reset, "payload");

    name = cJSON_GetArrayItem(payload, 0);
    wynik->name = malloc(sizeof(char)*(strlen(cJSON_Print(name)) + 1));
    strcpy(wynik->name, cJSON_Print(name));

    current_x = cJSON_GetArrayItem(payload, 1);
    wynik->x = atoi(cJSON_Print(current_x));

    current_y = cJSON_GetArrayItem(payload, 2);
    wynik->y = atoi(cJSON_Print(current_y));

    current_session = cJSON_GetArrayItem(payload, 3);
    wynik->session = malloc(sizeof(char)*(strlen(cJSON_Print(current_session)) + 1));
    strcpy(wynik->session, cJSON_Print(current_session));

    direction = cJSON_GetArrayItem(payload, 4);
    wynik->direction = malloc(sizeof(char)*(strlen(cJSON_Print(direction)) + 1));
    strcpy(wynik->direction, cJSON_Print(direction));

    step = cJSON_GetArrayItem(payload, 5);
    wynik->step = atoi(cJSON_Print(step));

    field_type = cJSON_GetArrayItem(payload, 6);
    wynik->field_type = malloc(sizeof(char)*(strlen(cJSON_Print(field_type)) + 1));
    strcpy(wynik->field_type, cJSON_Print(field_type));

    field_bonus = cJSON_GetArrayItem(payload, 7);
    wynik->field_bonus = malloc(sizeof(char)*(strlen(cJSON_Print(field_bonus)) + 1));
    strcpy(wynik->field_bonus, cJSON_Print(field_bonus));

    free(url);
    return wynik;
}

void wypisz(Mapa *A, int x, int y){
    printf("  ");
    for(int j = 0; j < 50; j++){
            printf("%4d", j-25); //wypisuje nr kolumny
    }
    printf("\n");
    for(int i = 0; i < 50; i++){
        printf("   ");
        for(int j = 0; j < 50; j++){
            printf("+---"); //wypisuje rozdzielenie miedzy wierszami
        }
        printf("+\n%3d", 25-i); //wypisuje numer wiersza
        for(int j = 0; j < 50; j++){
            if(25 - y == i && x + 25 == j){
                printf("|");
                printf(ANSI_COLOR_RED);
                printf("%2d ", A->field_type[i][j]);
                printf(ANSI_COLOR_RESET);
            }
            else
            {
                printf("|%2d ", A->field_type[i][j]);
            }
            
        }
        printf("|\n");
    }
    printf("  ");
    for(int j = 0; j < 50; j++){
        printf("+---"); //wypisuje rozdzielenie miedzy wierszami
    }
    printf("+\n\n");
}

int type(char* nazwa){
    if(strcmp(nazwa, "\"grass\"") == 0){
        return 1;
    }
    else if(strcmp(nazwa, "\"sand\"") == 0){
        return 2;
    }
    else if(strcmp(nazwa, "\"wall\"") == 0){
        return 3;
    }
    else return -1;
}