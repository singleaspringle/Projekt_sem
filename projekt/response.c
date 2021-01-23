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

Response* get_struct(char* token, char *command)
{
    char* request = get_request(token, command);
    Response* wynik = calloc(1, sizeof(Response));
    cJSON* json = cJSON_Parse(request);

    if(json == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    wynik->status = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(json, "status"));

    wynik->name = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 0));

    wynik->x = (int) cJSON_GetNumberValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 1));

    wynik->y = (int) cJSON_GetNumberValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 2));

    wynik->session = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 3));

    wynik->direction = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 4));

    wynik->step = (int) cJSON_GetNumberValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 5));

    wynik->field_type = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 6));

    wynik->field_bonus = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "payload"), 7));

    cJSON_free(json);
    //cJSON_Delete(json);
    free(request);

    return wynik;
} 

Lista* get_explore(char *token)
{
    char* request = get_request(token, "explore");
    Lista* wynik = calloc(1, sizeof(Lista));
    cJSON* json = cJSON_Parse(request);

    wynik->l1 = calloc(1, sizeof(Pole));
    wynik->l2 = calloc(1, sizeof(Pole));
    wynik->l3 = calloc(1, sizeof(Pole));

    if(json == NULL){
        const char* error_ptr = cJSON_GetErrorPtr();
        if(error_ptr != NULL){
            printf("Error before: %s\n", error_ptr);
        }
    }

    wynik->status = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(json, "status"));

    wynik->l1->x = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "x"));
    wynik->l1->y = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "y"));
    wynik->l1->field_type = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 0), "type"));

    wynik->l2->x = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "x"));
    wynik->l2->y = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "y"));
    wynik->l2->field_type = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 1), "type"));

    wynik->l3->x = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "x"));
    wynik->l3->y = (int) cJSON_GetNumberValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "y"));
    wynik->l3->field_type = cJSON_GetStringValue(cJSON_GetObjectItemCaseSensitive(cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(json, "payload"), "list"), 2), "type"));

    cJSON_free(json);
    //cJSON_Delete(json);
    free(request);

    return wynik;
}