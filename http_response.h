#pragma once
#include <stdio.h>

inline void build_http_200(char* dest, const char* body) {
    sprintf(dest, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s", strlen(body), body);
}
