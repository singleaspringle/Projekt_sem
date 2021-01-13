#include "list.h"

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

Lista* exploruj(char *token)
{
    char *url = (char*) malloc(sizeof(char)*(strlen("http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/")+strlen(token)+1));
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/");
    strcat(url, token);

    cJSON* explore = NULL;    
    cJSON* status = NULL;
    cJSON* payload = NULL;
    cJSON* list = NULL;
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
    // cJSON_free(list3->child->next->next);
    // cJSON_free(list3->child->next);
    // cJSON_free(list3->child);
    // cJSON_free(list3);
    // cJSON_free(list2->child->next->next);
    // cJSON_free(list2->child->next);
    // cJSON_free(list2->child);
    // cJSON_free(list2);
    // cJSON_free(list1->child->next->next);
    // cJSON_free(list1->child->next);
    // cJSON_free(list1->child);
    // cJSON_free(list1);
    // cJSON_free(list);
    // cJSON_free(status);
    // cJSON_free(payload);
    // free(wynik);
    //cJSON_Delete(explore);
    return wynik;
}

