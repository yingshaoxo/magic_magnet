#include "./c_python.h"


int main()
{
    const char *result = ypython_run_command("echo 'hi'");
    const char *new_result = ypython_string_strip((char *)result);
    if (_ypython_string_compare(new_result, "hi") != 0)
    {
        _ypython_print_formated_string("'hi' should equal to '%s'\n", new_result);
        exit(0);
    }

    ///////////////////////////////////////////////////////

    ypython_run("uname -v");

    //////////////////////////////////////////////////////

    _ypython_print_formated_string("Hi, '%s'.\n", "yingshaoxo");

    //////////////////////////////////////////////////////

    _Float *a_float = Float(3.2);
    _ypython_print_formated_string("%.3Lf\n", a_float->value);

    _Float *another_float = Float(1.8);
    _Float *sum = a_float->_Float_add(a_float, another_float);
    _ypython_print_formated_string("%.3Lf\n", sum->value);

    long double sum_float = 5.0;
    if (_ypython_get_float_absolute_value(sum->value - sum_float) > 0.0001) {
        _ypython_print_formated_string("%.8Lf should equal to %.8Lf\n", sum->value, sum_float);
    }

    //////////////////////////////////////////////////////

}