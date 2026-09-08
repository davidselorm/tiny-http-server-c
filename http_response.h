#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int status_code;
    char status_text[64];
    char headers[16][128];
    int header_count;
    char body[1024];
} HttpResponse;

static inline void http_response_init(HttpResponse* res) {
    res->status_code = 200;
    strcpy(res->status_text, "OK");
    res->header_count = 0;
    res->body[0] = '\0';
    // Default headers
    strcpy(res->headers[res->header_count++], "Server: tiny-http-server-c/1.0");
    strcpy(res->headers[res->header_count++], "Connection: close");
}

static inline void http_response_set_status(HttpResponse* res, int code, const char* text) {
    res->status_code = code;
    strncpy(res->status_text, text, sizeof(res->status_text) - 1);
}

static inline void http_response_set_header(HttpResponse* res, const char* key, const char* val) {
    if (res->header_count < 16) {
        snprintf(res->headers[res->header_count++], 128, "%s: %s", key, val);
    }
}

static inline void http_response_set_body(HttpResponse* res, const char* body) {
    strncpy(res->body, body, sizeof(res->body) - 1);
}

static inline int http_response_serialize(const HttpResponse* res, char* out, size_t out_len) {
    int written = snprintf(out, out_len, "HTTP/1.1 %d %s\r\n", res->status_code, res->status_text);
    for (int i = 0; i < res->header_count; i++) {
        written += snprintf(out + written, out_len - written, "%s\r\n", res->headers[i]);
    }
    written += snprintf(out + written, out_len - written, "Content-Length: %zu\r\n\r\n%s", strlen(res->body), res->body);
    return written;
}

#endif
