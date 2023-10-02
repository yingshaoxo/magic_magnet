#define HTTPSERVER_IMPL
#define EPOLL
#include "./dependencies/http_server/httpserver.h"

#include "./dependencies/yingshaoxo_c/c_python.h"

#define RESPONSE "Hello, World!"

void handle_request(struct http_request_s *request)
{
    // http_string_t body = http_request_body(request);
    // printf("\n%s\n", body.buf);

    // http_string_t jwt = http_request_header(request, "jwt");
    // printf("\n%s\n", jwt.buf);

    http_string_t method = http_request_method(request);
    // int split_length = 0;
    // ss* parts = ss_split_raw(method.char_list, ' ', &split_length);
    // printf("\n%s\n", parts[0]->buf);

    hello_yingshaoxo();

    struct http_response_s *response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, RESPONSE, sizeof(RESPONSE) - 1);
    http_respond(request, response);
}

int main()
{
    struct http_server_s *server = http_server_init(8000, handle_request);
    http_server_listen(server);
    printf("done\n");
}