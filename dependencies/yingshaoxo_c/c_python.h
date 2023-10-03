// #ifndef stdio.h
// #define stdio.h
#include <stdio.h>
// #endif
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Say hello to yingshaoxo.
*/
void hello_yingshaoxo()
{
    printf("Hello, world!\n");
}

/*
##################################################
Let's give those built-in c functions another name
##################################################
*/

// We could directly use '#define' to set a global replacement for function, but for the argurments hint, I choose not to do so.
// #define _ypython_resize_memory_block(buf,size) realloc(buf, size)

/*
Print formated string.
*/
#define _ypython_print_formated_string(string_format, ...) printf(string_format, __VA_ARGS__);                \
// #define _ypython_print_formated_string(string_format, ...) \
//     do                                              \
//     {                                               \
//         printf(string_format, __VA_ARGS__);                \
//     } while (0)

/*
The C library function `void *realloc(void *ptr, size_t size)` attempts to resize the memory block pointed to by `ptr` that was previously allocated with a call to `malloc` or `calloc`.
*/
void *_ypython_resize_memory_block_for_a_pointer(void *__ptr, size_t __size)
{
    return realloc(__ptr, __size);
}

/*
Get a newline-terminated string of finite length from STREAM.

This function is a possible cancellation point and therefore not
marked with __THROW.
*/
char *_ypython_get_a_newline_terminated_string_of_finite_length_from_a_STREAM(char *__restrict__ __s, int __n, FILE *__restrict__ __stream)
{
    return fgets(__s, __n, __stream);
}

/*
Return the EOF(end of file) indicator for STREAM.
*/
int _ypython_return_end_of_file_indicator_for_a_STREAM(FILE *__stream)
{
    return feof(__stream);
}

/*
The C library function `size_t strlen(const char *str)` computes the length of the string `str` up to, but not including the terminating null character.
*/
size_t _ypython_get_string_length(const char *__s)
{
    return strlen(__s);
}

/*
The popen function executes the shell command command as a subprocess.
However, instead of waiting for the command to complete, it creates a pipe to the subprocess and returns a stream that corresponds to that pipe.
*/
FILE *_ypython_execute_shell_command_as_a_subprocess_pipe_stream(const char *command, const char *mode)
{
    return popen(command, mode);
}

/*
The pclose() function closes a stream that was opened by popen(), waits for the command specified as an argument in popen() to terminate.
It returns the status of the process that was running the shell command.
*/
int _ypython_close_subprocess_pipe_stream(FILE *stream)
{
    return pclose(stream);
}

/*
The strcmp() compares two strings character by character. If the strings are equal, the function returns 0.
*/
int _ypython_string_compare(const char *str1, const char *str2)
{
    return strcmp(str1, str2);
}

/*
##################################################
Let's use those built-in c functions to do some useful things
##################################################
*/

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

char *_ypython_get_infinate_length_text_line(FILE *f)
{
    size_t size = 0;
    size_t len = 0;
    size_t last = 0;
    char *buf = NULL;

    do
    {
        size += BUFSIZ;                                              /* BUFSIZ is defined as "the optimal read size for this platform" */
        buf = _ypython_resize_memory_block_for_a_pointer(buf, size); /* realloc(NULL,n) is the same as malloc(n) */
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        if (buf == NULL)
            return NULL;
        _ypython_get_a_newline_terminated_string_of_finite_length_from_a_STREAM(buf + last, BUFSIZ, f);
        len = _ypython_get_string_length(buf);
        last = len - 1;
    } while (!_ypython_return_end_of_file_indicator_for_a_STREAM(f) && buf[last] != '\n');

    return buf;
}

char *_ypython_get_infinate_length_text(FILE *f)
{
    size_t size = 0;
    size_t len = 0;
    size_t last = 0;
    char *buf = NULL;

    do
    {
        size += BUFSIZ;                                              /* BUFSIZ is defined as "the optimal read size for this platform" */
        buf = _ypython_resize_memory_block_for_a_pointer(buf, size); /* realloc(NULL,n) is the same as malloc(n) */
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        if (buf == NULL)
            return NULL;
        _ypython_get_a_newline_terminated_string_of_finite_length_from_a_STREAM(buf + last, BUFSIZ, f);
        len = _ypython_get_string_length(buf);
        last = len - 1;

        if (buf[last] == '\n')
        {
            last = len;
        }
    } while (!_ypython_return_end_of_file_indicator_for_a_STREAM(f));

    return buf;
}

/*
Run a bash command and return the result as a string.
*/
const char *ypython_run_command(const char *bash_command_line)
{
    FILE *FileOpen;
    FileOpen = _ypython_execute_shell_command_as_a_subprocess_pipe_stream(bash_command_line, "r");

    char *all_lines = _ypython_get_infinate_length_text(FileOpen);
    _ypython_close_subprocess_pipe_stream(FileOpen);

    return ypython_string_strip(all_lines);
}

/*
Run a bash command and wait for it to get finished, it won't return anything.
*/
void ypython_run(const char *bash_command_line)
{
    FILE *FileOpen;
    FileOpen = _ypython_execute_shell_command_as_a_subprocess_pipe_stream(bash_command_line, "r");

    while (!_ypython_return_end_of_file_indicator_for_a_STREAM(FileOpen))
    {
        char *a_line = _ypython_get_infinate_length_text_line(FileOpen);
        printf("%s", a_line);
    }

    _ypython_close_subprocess_pipe_stream(FileOpen);
}

/*
Python_like print function.
*/
void ypython_print(const char *text)
{
    printf("%s\n", text);
}