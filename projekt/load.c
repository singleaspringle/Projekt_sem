#include "load.h"

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
        if (res != CURLE_OK){
            curl_easy_cleanup(curl);
            return "Błąd!\n";
        }
        else
        {
            /* zawsze po sobie sprzątaj */
            curl_easy_cleanup(curl);
            return chunk.response;
        }
    }
}

char* get_request(char* token, char* command){ //zwraca w formacie jsona
    char* url;
    if(strcmp(command, "rotate_left") != 0 && strcmp(command, "rotate_right") != 0){
        url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/") + strlen(command) + 1 + strlen(token) + 1));
        strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/");
        strcat(url, command);
        strcat(url, "/");
        strcat(url, token);
    }
    else if(strcmp(command, "rotate_left") == 0){
        url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/left/") + strlen(token) + 1));
        strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/");
        strcat(url, token);
        strcat(url, "/");
        strcat(url, "left");
    }
    else if(strcmp(command, "rotate_right") == 0){
        url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/right/") + strlen(token) + 1));
        strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/");
        strcat(url, token);
        strcat(url, "/");
        strcat(url, "right");
    }

    char* response = make_request(url);
    
    free(url);
    return response;
}







