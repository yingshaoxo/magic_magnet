#define HTTPSERVER_IMPL
#define EPOLL
#include "./dependencies/http_server/httpserver.h"

#include "./dependencies/yingshaoxo_c/c_python.h"

#include <stdio.h>

#define RESPONSE "Hello, World!"

void handle_request(struct http_request_s *request)
{

    http_string_t url = http_request_target(request);
    printf("\n%s\n", url.char_list);

    http_string_t body = http_request_body(request);
    printf("\n%s\n", body.char_list);

    http_string_t jwt = http_request_header(request, "jwt");
    printf("\n%s\n", jwt.char_list);

    http_string_t method = http_request_method(request);
    printf("\n%s\n", method.char_list);

    printf("\n\n______________________\n\n");

    struct http_response_s *response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/plain");
    http_response_body(response, RESPONSE, sizeof(RESPONSE) - 1);
    http_respond(request, response);
}

int main()
{
    // struct http_server_s *server = http_server_init(8000, handle_request);
    // http_server_listen(server);
    // printf("done\n");

    const char* result = ypython_run_command("uname -a");
    printf("%s", result);

    // ypython_run("uname -v");

    // ypython_print("hi, you");
}