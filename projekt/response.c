#include "response.h"

Response* get_struct(char* token, char *command)
{
    char* request = get_request(token, command);
    Response* wynik = calloc(1, sizeof(Response));
    cJSON* json = cJSON_Parse(request);

    wynik->status = calloc(8, sizeof(char));
    wynik->name = calloc(15, sizeof(char));
    wynik->session = calloc(100, sizeof(char));
    wynik->direction = calloc(2, sizeof(char));
    wynik->field_type = calloc(6, sizeof(char));
    wynik->field_bonus = calloc(15, sizeof(char));

    if(json == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    strcpy(wynik->status, cJSON_GetObjectItemCaseSensitive(json, "status")->valuestring);

    strcpy(wynik->name, cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 0)->valuestring);

    wynik->x = (int) cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 1)->valueint;

    wynik->y = (int) cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 2)->valueint;

    strcpy(wynik->session, cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 3)->valuestring);

    strcpy(wynik->direction, cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 4)->valuestring);

    wynik->step = (int) cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 5)->valueint;

    strcpy(wynik->field_type, cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 6)->valuestring);

    strcpy(wynik->field_bonus, cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 7)->valuestring);

    //cJSON_free(json);
    cJSON_Delete(json);
    free(request);

    return wynik;
} 

List* get_explore(char *token)
{
    char* request = get_request(token, "explore");
    List* wynik = calloc(1, sizeof(List));
    cJSON* json = cJSON_Parse(request);

    wynik->status = calloc(8, sizeof(char));

    wynik->l1 = calloc(1, sizeof(Field));
    wynik->l2 = calloc(1, sizeof(Field));
    wynik->l3 = calloc(1, sizeof(Field));

    wynik->l1->field_type = calloc(6, sizeof(char));
    wynik->l2->field_type = calloc(6, sizeof(char));
    wynik->l3->field_type = calloc(6, sizeof(char));

    if(json == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    
    strcpy(wynik->status, cJSON_GetObjectItemCaseSensitive(json, "status")->valuestring);

    wynik->l1->x = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "x")->valueint;
    wynik->l1->y = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "y")->valueint;
    strcpy(wynik->l1->field_type, cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "type")->valuestring);

    wynik->l2->x = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "x")->valueint;
    wynik->l2->y = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "y")->valueint;
    strcpy(wynik->l2->field_type, cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "type")->valuestring);

    wynik->l3->x = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "x")->valueint;
    wynik->l3->y = (int) cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "y")->valueint;
    strcpy(wynik->l3->field_type, cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "type")->valuestring);

    //cJSON_free(json);
    cJSON_Delete(json);
    free(request);

    return wynik;
}

void free_explore(List* explore){
    free(explore->status);
    free(explore->l1->field_type);
    free(explore->l2->field_type);
    free(explore->l3->field_type);
    free(explore->l1);
    free(explore->l2);
    free(explore->l3);
    free(explore);
}

void free_response(Response* response){
    free(response->field_bonus);
    free(response->field_type);
    free(response->name);
    free(response->session);
    free(response->direction);
    free(response->status);
    free(response);
}