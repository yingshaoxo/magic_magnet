// #ifndef stdio.h
// #define stdio.h
#include <stdio.h>
// #endif
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
Get the absolute value of a floating point number.
*/

double _ypython_get_float_absolute_value(double __x) {
    return fabs(__x);
}

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
The C library function `char *strcat(char *dest, const char *src)` appends the string pointed to by src to the end of the string pointed to by dest.
In other words, second string will get added to the end of the first string.
*/
char *_ypython_string_adding(char *dest, const char *src) {
    return strcat(dest, src);
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

    return all_lines;
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


/*
##################################################
Let's create some built-in data types that similar to python data types
For example, str, double, int, bool, dict, list and so on
##################################################
*/

/*
None type
*/
typedef struct Type_Ypython_None Type_Ypython_None;
struct Type_Ypython_None {
    int value;
    bool is_none;
    char *type;
};

Type_Ypython_None *Ypython_None() {
    Type_Ypython_None *new_none_value;
    new_none_value = malloc(sizeof(Type_Ypython_None));
    new_none_value -> type = "none";

    new_none_value->is_none = true;
    new_none_value->value = 0;

    return new_none_value;
}

/*
String type
*/
typedef struct Type_Ypython_String Type_Ypython_String;
struct Type_Ypython_String {
    char *value;
    bool is_none;
    char *type;
    Type_Ypython_String *(*function_add)(Type_Ypython_String *self, Type_Ypython_String *another_string);
    bool (*function_is_equal)(Type_Ypython_String *self, Type_Ypython_String *another_string);
};

Type_Ypython_String *Type_Ypython_String_add(Type_Ypython_String *self, Type_Ypython_String *another_string) {
    Type_Ypython_String *new_string_value;
    new_string_value = malloc(sizeof(Type_Ypython_String));
    new_string_value->type = "string";

    if (self->is_none || another_string->is_none) {
        new_string_value->value = "";
        new_string_value->is_none = true;
    } else {
        new_string_value->is_none = false;

        size_t total_length = _ypython_get_string_length(self->value) + _ypython_get_string_length(another_string->value);
        char *new_chars_value = malloc(total_length);
        snprintf(new_chars_value, total_length+1, "%s%s", self->value, another_string->value);

        new_string_value->value = new_chars_value;
    }

    return new_string_value;
}

bool Type_Ypython_String_is_equal(Type_Ypython_String *self, Type_Ypython_String *another_string) {
    if (self->is_none && another_string->is_none) {
        return true;
    }
    else if ((!(self->is_none)) && (another_string->is_none)) {
        return false;
    }
    else if ((self->is_none) && (!(another_string->is_none))) {
        return false;
    } else {
        if (_ypython_string_compare(self->value, another_string->value) == 0) {
            return true;
        } else {
            return false;
        }
    }
}

Type_Ypython_String *Ypython_String(char *value) {
    Type_Ypython_String *new_string_value;
    new_string_value = malloc(sizeof(Type_Ypython_String));
    new_string_value->type = "string";

    new_string_value->is_none = false;
    new_string_value->value = value;

    new_string_value->function_add = &Type_Ypython_String_add;
    new_string_value->function_is_equal = &Type_Ypython_String_is_equal;

    return new_string_value;
}

/*
Bool type
*/
typedef struct Type_Ypython_Bool Type_Ypython_Bool;
struct Type_Ypython_Bool {
    bool value;
    bool is_none;
    char *type;
};

Type_Ypython_Bool *Ypython_Bool(bool value) {
    Type_Ypython_Bool *new_bool_value;
    new_bool_value = malloc(sizeof(Type_Ypython_Bool));
    new_bool_value -> type = "bool";

    new_bool_value->is_none = false;
    new_bool_value->value = value;

    return new_bool_value;
}


/*
Int type
*/
typedef struct Type_Ypython_Int Type_Ypython_Int;
struct Type_Ypython_Int {
    long long value;
    bool is_none;
    char *type;
    Type_Ypython_Int *(*function_add)(Type_Ypython_Int *self, Type_Ypython_Int *another_int);
    Type_Ypython_Int *(*function_multiply)(Type_Ypython_Int *self, Type_Ypython_Int *another_int);
};

Type_Ypython_Int *Type_Ypython_Int_add(Type_Ypython_Int *self, Type_Ypython_Int *another_int) {
    Type_Ypython_Int *new_int_value;
    new_int_value = malloc(sizeof(Type_Ypython_Int));
    new_int_value->type = "int";

    if (self->is_none || another_int->is_none) {
        new_int_value->value = 0;
        new_int_value->is_none = true;
        return new_int_value;
    } else {
        new_int_value->is_none = false;
        new_int_value->value = self->value + another_int->value;
        return new_int_value;
    }
}

Type_Ypython_Int *Type_Ypython_Int_multiply(Type_Ypython_Int *self, Type_Ypython_Int *another_int) {
    Type_Ypython_Int *new_int_value;
    new_int_value = malloc(sizeof(Type_Ypython_Int));
    new_int_value->type = "int";

    if (self->is_none || another_int->is_none) {
        new_int_value->value = 0;
        new_int_value->is_none = true;
        return new_int_value;
    } else {
        new_int_value->is_none = false;
        new_int_value->value = self->value * another_int->value;
        return new_int_value;
    }
}

Type_Ypython_Int *Ypython_Int(long long value) {
    Type_Ypython_Int *new_int_value;
    new_int_value = malloc(sizeof(Type_Ypython_Int));
    new_int_value->type = "int";

    new_int_value->is_none = false;
    new_int_value->value = value;

    new_int_value->function_add = &Type_Ypython_Int_add;
    new_int_value->function_multiply = &Type_Ypython_Int_multiply;

    return new_int_value;
}

/*
Float type
*/
typedef struct Type_Ypython_Float Type_Ypython_Float;
struct Type_Ypython_Float {
    long double value;
    bool is_none;
    char *type;
    Type_Ypython_Float *(*function_add)(Type_Ypython_Float *self, Type_Ypython_Float *another_float);
    Type_Ypython_Float *(*function_multiply)(Type_Ypython_Float *self, Type_Ypython_Float *another_float);
};

Type_Ypython_Float *Type_Ypython_Float_add(Type_Ypython_Float *self, Type_Ypython_Float *another_float) {
    Type_Ypython_Float *new_float_value;
    new_float_value = malloc(sizeof(Type_Ypython_Float));
    new_float_value->type = "float";

    if (self->is_none || another_float->is_none) {
        new_float_value->value = 0;
        new_float_value->is_none = true;
        return new_float_value;
    } else {
        new_float_value->is_none = false;
        new_float_value->value = self->value + another_float->value;
        return new_float_value;
    }
}

Type_Ypython_Float *Type_Ypython_Float_multiply(Type_Ypython_Float *self, Type_Ypython_Float *another_float) {
    Type_Ypython_Float *new_float_value;
    new_float_value = malloc(sizeof(Type_Ypython_Float));
    new_float_value->type = "float";

    if (self->is_none || another_float->is_none) {
        new_float_value->value = 0;
        new_float_value->is_none = true;
        return new_float_value;
    } else {
        new_float_value->is_none = false;
        new_float_value->value = self->value * another_float->value;
        return new_float_value;
    }
}

Type_Ypython_Float *Ypython_Float(long double value) {
    Type_Ypython_Float *new_float_value;
    new_float_value = malloc(sizeof(Type_Ypython_Float));
    new_float_value->type = "float";

    new_float_value->is_none = false;
    new_float_value->value = value;

    new_float_value->function_add = &Type_Ypython_Float_add;
    new_float_value->function_multiply = &Type_Ypython_Float_multiply;

    return new_float_value;
}