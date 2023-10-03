#include "./c_python.h"


int main()
{
    const char *result = ypython_run_command("echo 'hi'");
    if (_ypython_string_compare(result, "hi") != 0)
    {
        _ypython_print_formated_string("'hi' should equal to '%s'\n", result);
        exit(0);
    }

    ///////////////////////////////////////////////////////

    ypython_run("uname -v");

    //////////////////////////////////////////////////////


    _ypython_print_formated_string("Hi, '%s'.\n", "yingshaoxo");
}