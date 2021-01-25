#include "../response.h"


int main(int argc, char* argv[]){
    if(argc != 2) abort();
    Response* response;
    List* explore;
    char* token = argv[1];

    response = get_struct(token, "info");
    printf("x: %d\ny: %d\nfield_type: %s\n", response->x, response->y, response->field_type);

    explore = get_explore(token);
    printf("x1: %d\ny1: %d\nfield_type: %s\n", explore->l1->x, explore->l1->y, explore->l1->field_type);

    free_response(response);
    free_explore(explore);

    return 0;
}