#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_response.h"

typedef struct {
    char method[16];
    char path[256];
    char version[16];
    char body[1024];
} HttpRequest;

int parse_http_request(const char* raw, HttpRequest* req) {
    if (!raw || !req) return -1;
    memset(req, 0, sizeof(HttpRequest));
    
    // Parse Request Line
    if (sscanf(raw, "%15s %255s %15s", req->method, req->path, req->version) < 2) {
        return -1;
    }
    
    // Locate Body after CRLF CRLF
    const char* body_start = strstr(raw, "\r\n\r\n");
    if (body_start) {
        strncpy(req->body, body_start + 4, sizeof(req->body) - 1);
    }
    return 0;
}

void route_request(const HttpRequest* req, HttpResponse* res) {
    if (strcmp(req->method, "GET") == 0) {
        if (strcmp(req->path, "/") == 0 || strcmp(req->path, "/health") == 0) {
            http_response_set_status(res, 200, "OK");
            http_response_set_header(res, "Content-Type", "application/json");
            http_response_set_body(res, "{\"status\":\"UP\",\"engine\":\"tiny-http-server-c\"}");
        } else if (strcmp(req->path, "/metrics") == 0) {
            http_response_set_status(res, 200, "OK");
            http_response_set_header(res, "Content-Type", "text/plain");
            http_response_set_body(res, "# HELP http_requests_total Total HTTP requests\nhttp_requests_total 42\n");
        } else {
            http_response_set_status(res, 404, "Not Found");
            http_response_set_header(res, "Content-Type", "application/json");
            http_response_set_body(res, "{\"error\":\"Resource Not Found\"}");
        }
    } else if (strcmp(req->method, "POST") == 0) {
        http_response_set_status(res, 201, "Created");
        http_response_set_header(res, "Content-Type", "application/json");
        http_response_set_body(res, "{\"status\":\"accepted\"}");
    } else {
        http_response_set_status(res, 405, "Method Not Allowed");
        http_response_set_body(res, "Method Not Allowed");
    }
}

int main(void) {
    printf("[tiny-http-server-c] HTTP Server Core Initialized.\n");
    
    // Self-test parser & routing
    const char* mock_req = "GET /health HTTP/1.1\r\nHost: localhost:8080\r\n\r\n";
    HttpRequest req;
    if (parse_http_request(mock_req, &req) == 0) {
        HttpResponse res;
        http_response_init(&res);
        route_request(&req, &res);
        
        char buffer[2048];
        http_response_serialize(&res, buffer, sizeof(buffer));
        printf("Verification Response:\n%s\n", buffer);
    }
    return 0;
}
