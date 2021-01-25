#include "../load.h"

int main(int argc, char* argv[]){
    if(argc != 2) abort();

    char* token = argv[1];
    FILE* fout = fopen("tests/derulo.json", "w+");
    fprintf(fout, "%s\n", get_request(token, "move"));
    fprintf(fout, "%s\n", get_request(token, "explore"));
    fclose(fout);
}