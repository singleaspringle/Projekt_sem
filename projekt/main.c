#include "load.h"
#include "logic.h"
#include "image.h"

//null - 0
//grass - 1
//sand - 2
//wall - 3

int main(int argc, char **argv)
{   
    char *token = argv[1];
    char command [30];

    Map* map = set_map(map, token);

    Response* response;
    Lista* explore;

    //testy:
    if(argc == 3){
        if(strcmp(argv[2], "test-load") == 0){
            FILE* fout = fopen("derulo.json", "w+");
            fprintf(fout, "%s\n", get_request(token, "move"));
            fprintf(fout, "%s\n", get_request(token, "explore"));
            fclose(fout);
        }
        else if(strcmp(argv[2], "test-response") == 0){
            FILE* fin = fopen("derulo.json", "r+");
            response = get_struct(token, "info");
            printf("x: %d\ny: %d\nfield_type: %s\n", response->x, response->y, response->field_type);
        }
        else if(strcmp(argv[2], "test-save-map") == 0){
            FILE* f = fopen("mapa.txt", "r+");
            map = bot(map, token);
            print_map(map);
            fprint_map(map, f);
            fclose(f);
            png_map("mapa.png", "tilesn.png", map);
        }
        else if(strcmp(argv[2], "test-load-map") == 0){
            FILE* f = fopen("mapa.txt", "r+");
            map = load_map(f);
            print_map(map);
            fclose(f);
            png_map("mapa.png", "tilesn.png", map);
        }
        else if(strcmp(argv[2], "test-seek-wall") == 0){
            map = seek_wall(map, token);
            print_map(map);
            png_map("mapa.png", "tilesn.png", map);
        }
        else if(strcmp(argv[2], "test-bot") == 0){
            map = bot(map, token);
            print_map(map);
            png_map("mapa.png", "tilesn.png", map);
        }
        else if(strcmp(argv[2], "reset") == 0){
            map = reset_map(map, token);
            print_map(map);
            png_map("mapa.png", "tilesn.png", map);
        }
    }
    if(argc == 2 || strcmp(argv[2], "test-load-map") == 0){ //czesc interaktywna, do latwiejszego testowania poprawnego dzialania programu. W finalnej wersji jej nie bedzie.
        print_map(map);
        while(1){ //zeby wyjsc z programu nalezy wcisnac ctrl + c
            fgets(command, 30, stdin);
            strcpy(command, strtok(command, "\n"));

            if(strcmp(command, "reset") == 0)
            {
                map = reset_map(map, token);
            }
            else if(strcmp(command, "explore") == 0)
            {
                explore = get_explore(token);
                map = interpret_explore(explore, map);
            }
            else
            {
                response = get_struct(token, command);
                map = interpret_response(response, map);
            }

            
            print_map(map);
            png_map("mapa.png", "tilesn.png", map);
        }
    }

    free(map);
    return 0;
}