#ifndef _REQUEST_H
#define _REQUEST_H

#ifdef __cplusplus

#include <string>

using namespace std;

class Request {
public:
    Request();
    Request(const char *url);
    ~Request();
    string getContent();
private:
    string _content = "";
    char _error_buffer[8096];
    void* _conn = nullptr;
};

extern "C" {
#endif

typedef struct {
    char *content; 
} response_t;

response_t *request_get(const char *url);
void        response_free(response_t *resp);

#ifdef __cplusplus
}
#endif

#endif /* _REQUEST_H */
