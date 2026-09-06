#include <stdio.h>
#include <string.h>

typedef struct {
    char method[16];
    char uri[256];
    char version[16];
} HttpRequest;

int parse_request_line(const char* raw, HttpRequest* req) {
    if (sscanf(raw, "%15s %255s %15s", req->method, req->uri, req->version) == 3) {
        return 0;
    }
    return -1;
}

int main() {
    printf("TinyHttpServer-C Engine Initialized.\n");
    return 0;
}
