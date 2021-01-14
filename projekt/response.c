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
    Response* wynik = calloc(1, sizeof(Response));
    cJSON* json = cJSON_Parse(get_request(token, command));

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

    return wynik;
}