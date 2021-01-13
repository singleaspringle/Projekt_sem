#include "response.h"

void clean_response (Response *dana)
{
    free (dana->status);
    free (dana->name);
    free (dana->session);
    free (dana->direction);
    free (dana->field_type);
    free (dana->field_bonus);
    free (dana);
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
    // cJSON_free(field_bonus);
    // cJSON_free(field_type);
    // cJSON_free(step);
    // cJSON_free(direction);
    // cJSON_free(current_session);
    // cJSON_free(current_y);
    // cJSON_free(current_x);
    // cJSON_free(name);
    // cJSON_free(payload);
    // cJSON_free(status);
    // free(wynik);
    //cJSON_Delete(reset);
    return wynik;
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
    // cJSON_free(field_bonus);
    // cJSON_free(field_type);
    // cJSON_free(step);
    // cJSON_free(direction);
    // cJSON_free(current_session);
    // cJSON_free(current_y);
    // cJSON_free(current_x);
    // cJSON_free(name);
    // cJSON_free(payload);
    // cJSON_free(status);
    //cJSON_Delete(info);
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
    // cJSON_free(field_bonus);
    // cJSON_free(field_type);
    // cJSON_free(step);
    // cJSON_free(direction);
    // cJSON_free(current_session);
    // cJSON_free(current_y);
    // cJSON_free(current_x);
    // cJSON_free(name);
    // cJSON_free(payload);
    // cJSON_free(status);
    // cJSON_free(move);
    // free(wynik);
    //cJSON_Delete(move);
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
    // cJSON_free(field_bonus);
    // cJSON_free(field_type);
    // cJSON_free(step);
    // cJSON_free(direction);
    // cJSON_free(current_session);
    // cJSON_free(current_y);
    // cJSON_free(current_x);
    // cJSON_free(name);
    // cJSON_free(payload);
    // cJSON_free(status);
    // free(wynik);
    //cJSON_Delete(rotate);
    return wynik;
}
