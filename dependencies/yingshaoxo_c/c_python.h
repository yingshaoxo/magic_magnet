// #ifndef stdio.h
// #define stdio.h
#include <stdio.h>
// #endif

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
The C library function `void *realloc(void *ptr, size_t size)` attempts to resize the memory block pointed to by `ptr` that was previously allocated with a call to `malloc` or `calloc`.
*/
void *_ypython_resize_memory_block_for_a_pointer(void *__ptr, size_t __size) {
    return realloc(__ptr, __size);
}

/*
Get a newline-terminated string of finite length from STREAM.

This function is a possible cancellation point and therefore not
marked with __THROW.
*/
char *_ypython_get_a_newline_terminated_string_of_finite_length_from_a_STREAM(char *__restrict__ __s, int __n, FILE *__restrict__ __stream) {
    return fgets(__s, __n, __stream);
}


/*
Return the EOF(end of file) indicator for STREAM.
*/
int _ypython_return_end_of_file_indicator_for_a_STREAM(FILE *__stream) {
    return feof(__stream);
}

/*
The C library function `size_t strlen(const char *str)` computes the length of the string `str` up to, but not including the terminating null character.
*/
size_t _ypython_get_string_length(const char *__s) {
    return strlen(__s);
}


/*
##################################################
Let's use those built-in c functions to do some useful things
##################################################
*/

char *_ypython_get_infinate_length_text_line(FILE *f)
{
    size_t size = 0;
    size_t len = 0;
    size_t last = 0;
    char *buf = NULL;

    do
    {
        size += BUFSIZ;           /* BUFSIZ is defined as "the optimal read size for this platform" */
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
        size += BUFSIZ;           /* BUFSIZ is defined as "the optimal read size for this platform" */
        buf = _ypython_resize_memory_block_for_a_pointer(buf, size); /* realloc(NULL,n) is the same as malloc(n) */
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        if (buf == NULL)
            return NULL;
        _ypython_get_a_newline_terminated_string_of_finite_length_from_a_STREAM(buf + last, BUFSIZ, f);
        len = _ypython_get_string_length(buf);
        last = len-1;

        if (buf[last] == '\n') {
            last = len;
        }
    } while (!_ypython_return_end_of_file_indicator_for_a_STREAM(f));

    return buf;
}

const char *ypython_run_command(const char *bash_command_line)
{
    FILE *FileOpen;
    FileOpen = popen("ls -l", "r");

    char *all_lines = _ypython_get_infinate_length_text(FileOpen);
    pclose(FileOpen);

    return all_lines;
}