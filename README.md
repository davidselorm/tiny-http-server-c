# tiny-http-server-c

A non-blocking POSIX C micro-HTTP/1.1 engine with zero external dependencies.

## Features
- **HTTP/1.1 RFC Compliance**: Complete request line and header tokenization.
- **Routing Engine**: RESTful endpoint handlers (`/health`, `/metrics`, fallback 404/405).
- **Embedded Response Serializer**: Automatic `Content-Length` calculation and status phrase mapping.
