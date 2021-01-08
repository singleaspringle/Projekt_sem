typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
char* info(char *token);
char* move(char *token);
char* rotate(char *token, char *rotation);
char* explore(char *token);
char* reset(char *token);
void bot(char *token);