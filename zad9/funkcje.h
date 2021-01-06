typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);
char *make_request(char *url);
void info(char *token);
void move(char *token);
void rotate(char *token, char *rotation);
void explore(char *token);
void reset(char *token);
