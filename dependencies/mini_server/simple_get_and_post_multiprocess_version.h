// You can implement `url_handler()` function to modifiying the server functionality

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*
The C library function `char *strstr(const char *haystack, const char *needle)` function finds the first occurrence of the substring needle in the string haystack.
It will return null pointer if the sub_sequence is not present in haystack.
The terminating '\0' characters are not compared.
*/
char *_ypython_find_the_first_sub_string_in_a_string(const char *a_string, const char *sub_string)
{
    return strstr(a_string, sub_string);
}

long long _ypython_string_count_sub_string(const char *a_string, const char *sub_string)
{
    long long counting = 0;
    const char *temprary = a_string;
    temprary = _ypython_find_the_first_sub_string_in_a_string(temprary, sub_string);
    while (temprary != NULL)
    {
        counting++;

        temprary++;
        temprary = _ypython_find_the_first_sub_string_in_a_string(temprary, sub_string);
    }
    return counting;
}

bool _ypython_is_general_space(char c)
{
    switch (c)
    {
    case ' ':
    case '\n':
    case '\t':
    case '\f':
    case '\r':
        return true;
        break;
    default:
        return false;
        break;
    }
}

char *_ypython_string_left_strip(char *s)
{
    while (_ypython_is_general_space(*s))
    {
        s++;
    }
    return s;
}

char *_ypython_string_right_strip(char *s)
{
    char *back = s + strlen(s) - 1;
    while (_ypython_is_general_space(*back))
    {
        --back;
    }
    *(back + 1) = '\0';
    return s;
}

/*
strip \s before and after a string.
*/
const char *ypython_string_strip(char *s)
{
    return (const char *)_ypython_string_right_strip(_ypython_string_left_strip(s));
}

// Client request

char *method, // "GET" or "POST"
    *uri,     // "/index.html" things before '?'
    *queries,      // "a=1&b=2"     things after  '?'
    *http_protocol_version;    // "HTTP/1.1"

char *payload; // for POST
int payload_size;

/*
Real code started
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#define CONNMAX 1000

static int listenfd, clients[CONNMAX];
static void error(char *);
static void start_server(const char *);
static void handle_function_in_sub_process_based_on_current_global_variable(int);

typedef struct header_t header_t;
struct header_t
{
    char *name;
    char *value;
};

static int global_socket_client_file_descriptor;
static char *global_html_request_raw_text;

// user shall implement this function:
void url_handler(int socket_client_file_descriptor, header_t header_values[], char *method, char *uri, char *url_queries, char *post_payload, int payload_size);

void serve_forever(const char *PORT)
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    char c;

    int slot = 0;

    printf(
        "Server started %shttp://127.0.0.1:%s%s\n",
        "\033[92m", PORT, "\033[0m");

    // Setting all elements to -1: signifies there is no client connected
    int i;
    for (i = 0; i < CONNMAX; i++) {
        clients[i] = -1;
    }
    start_server(PORT);

    // Ignore SIGCHLD to avoid zombie threads
    signal(SIGCHLD, SIG_IGN);

    // ACCEPT connections
    while (1)
    {
        addrlen = sizeof(clientaddr);
        clients[slot] = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);

        if (clients[slot] < 0)
        {
            perror("accept() error");
        }
        else
        {
            if (fork() == 0)
            {
                handle_function_in_sub_process_based_on_current_global_variable(slot);
                exit(0);
            }
        }

        while (clients[slot] != -1)
            slot = (slot + 1) % CONNMAX;
    }
}

// start server
void start_server(const char *port)
{
    struct addrinfo hints, *res, *p;

    // getaddrinfo for host
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, port, &hints, &res) != 0)
    {
        perror("getaddrinfo() error");
        exit(1);
    }
    // socket and bind
    for (p = res; p != NULL; p = p->ai_next)
    {
        int option = 1;
        listenfd = socket(p->ai_family, p->ai_socktype, 0);
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
        if (listenfd == -1)
            continue;
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break;
    }
    if (p == NULL)
    {
        perror("socket() or bind()");
        exit(1);
    }

    freeaddrinfo(res);

    // listen for incoming connections
    if (listen(listenfd, 1000000) != 0)
    {
        perror("listen() error");
        exit(1);
    }
}

// get request header
char *get_request_header_by_name(header_t header_values[], const char *name)
{
    int index = 0;
    while (index < 30)
    {
        if (header_values[index].name) {
            if (name) {
                if (strcmp(header_values[index].name, name) == 0) {
                    return header_values[index].value;
                }
            }
        }
        index += 1;
    }
    return NULL;
}

void send_socket_data_out(int socket_client_file_descriptor, char *data)
{
    send(socket_client_file_descriptor, data, strlen(data), 0);
}

// client connection
void handle_function_in_sub_process_based_on_current_global_variable(int n)
{
    int rcvd, fd, bytes_read;
    char *ptr;

    global_html_request_raw_text = malloc(65535);
    rcvd = recv(clients[n], global_html_request_raw_text, 65535, 0);

    // fprintf(stderr, "\n%s\n", global_html_request_raw_text);

    if (rcvd < 0) // receive error
        fprintf(stderr, ("recv() error\n"));
    else if (rcvd == 0) // receive socket closed
        fprintf(stderr, "Client disconnected upexpectedly.\n");
    else // message received
    {
        global_html_request_raw_text[rcvd] = '\0';

        long long loop_times = _ypython_string_count_sub_string((const char *)global_html_request_raw_text, "\r\n");
        loop_times -= 2;

        method = strtok(global_html_request_raw_text, " \t\r\n");
        uri = strtok(NULL, " \t");
        http_protocol_version = strtok(NULL, " \t\r\n");

        fprintf(stderr, "\x1b[32m + [%s] %s\x1b[0m\n", method, uri);

        if (queries = strchr(uri, '?'))
        {
            *queries++ = '\0'; // split URI
        }
        else
        {
            queries = uri - 1; // use an empty string
        }

        header_t header_values[30] = {{"\0", "\0"}};
        int index = 0;
        while (loop_times >= 0)
        {
            char *k, *v;

            k = strtok(NULL, ":");
            if (!k)
            {
                payload = "";
                break;
            }
            if (strchr(k, '{') != NULL)
            {
                char *fake_payload = strtok(NULL, "\r\n");
                payload = strcat(k, fake_payload);
                while (fake_payload != NULL)
                {
                    fake_payload = strtok(NULL, "\r\n");
                    if (fake_payload != NULL)
                    {
                        char *new_text = malloc(sizeof(payload) + sizeof("\r\n") + sizeof(fake_payload));
                        strcat(new_text, "\r\n");
                        strcat(new_text, fake_payload);
                        strcat(payload, new_text);
                    } else {
                        break;
                    }
                }
                payload = (char *)ypython_string_strip(payload);
                break;
            }
            k++;
            v = strtok(NULL, "\r\n");
            if (!v)
            {
                payload = "";
                break;
            }
            v++;
            header_values[index].name = k;
            header_values[index].value = v;
            fprintf(stderr, "[Header] %s:%s\n", k, v);

            loop_times -= 1;
            index += 1;
        }
        char *a_header = get_request_header_by_name(header_values, "Content-Length"); // and the related header if there is
        if (a_header == NULL)
        {
            payload_size = 0;
        }
        else
        {
            payload_size = atol(a_header);
        }

        fprintf(stderr, "[payload] %s\n", payload);
        fprintf(stderr, "[payload_size] %d\n", payload_size);

        // bind global_socket_client_file_descriptor to stdout, making it easier to write
        global_socket_client_file_descriptor = clients[n];

        // call router
        url_handler(global_socket_client_file_descriptor, header_values, method, uri, queries, payload, payload_size);

        shutdown(global_socket_client_file_descriptor, SHUT_WR);
        close(global_socket_client_file_descriptor);
    }

    // Closing SOCKET
    shutdown(global_socket_client_file_descriptor, SHUT_RDWR); // All further send and recieve operations are DISABLED...
    close(global_socket_client_file_descriptor);
    clients[n] = -1;
}

void url_handler(int socket_client_file_descriptor, header_t header_values[], char *method, char *uri, char *url_queries, char *post_payload, int payload_size)
{
    if (0)
    {
    }
    else if (strcmp("/", uri) == 0 && strcmp("GET", method) == 0)
    {
        char *response = "HTTP/1.1 200 OK\r\n\r\n"
                         "Hello, you are using GET requests";
        send_socket_data_out(socket_client_file_descriptor, response);
    }
    else if (strcmp("/", uri) == 0 && strcmp("POST", method) == 0)
    {
        char *response = malloc(65535);
        sprintf(response,
                "HTTP/1.1 200 OK\r\n\r\n"
                "Wow, you are using post, and you sent me %s length of data. \r\n",
                get_request_header_by_name(header_values, "Content-Length"));
        send_socket_data_out(socket_client_file_descriptor, response);
    }
    else
    {
        char *response = malloc(65535);
        sprintf(response,
                "HTTP/1.1 500 Not Handled\r\n\r\n"
                "The server has no handler to the request. \r\n");
        send_socket_data_out(socket_client_file_descriptor, response);
    }
}