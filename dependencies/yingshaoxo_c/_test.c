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

    Type_Ypython_Float *a_float = Ypython_Float(3.2);
    _ypython_print_formated_string("%.3Lf\n", a_float->value);

    Type_Ypython_Float *another_float = Ypython_Float(1.8);
    Type_Ypython_Float *sum = a_float-> function_add(a_float, another_float);
    _ypython_print_formated_string("%.3Lf\n", sum->value);

    long double sum_float = 5.0;
    if (_ypython_get_float_absolute_value(sum->value - sum_float) > 0.0001) {
        _ypython_print_formated_string("%.8Lf should equal to %.8Lf\n", sum->value, sum_float);
    }

    //////////////////////////////////////////////////////

    Type_Ypython_Int *a_int = Ypython_Int(3);
    _ypython_print_formated_string("%lld\n", a_int->value);

    Type_Ypython_Int *another_int = Ypython_Int(2);
    Type_Ypython_Int *sum_int = a_int-> function_add(a_int, another_int);
    _ypython_print_formated_string("%lld\n", sum_int->value);

    long long sum_int2 = 5;
    if (sum_int2 != sum_int->value) {
        _ypython_print_formated_string("%lld should equal to %lld\n", sum_int->value, sum_int2);
    }

    //////////////////////////////////////////////////////

    Type_Ypython_String *a_string = Ypython_String("yingshaoxo");
    ypython_print(a_string->value);

    Type_Ypython_String *another_string = Ypython_String(" is super nice.");
    Type_Ypython_String *final_string = a_string->function_add(a_string, another_string);

    Type_Ypython_String *target_string = Ypython_String("yingshaoxo is super nice.");
    if (!(target_string->function_is_equal(target_string, final_string))) {
        _ypython_print_formated_string("'%s' should equal to '%s'\n", final_string->value, target_string->value);
    }

    //////////////////////////////////////////////////////

    if (!_ypython_string_is_sub_string("abc", "ab")) {
        ypython_print("'ab' should be a substring of 'abc'");
    };

    if (_ypython_string_is_sub_string("abc", "ac")) {
        ypython_print("'ab' should not be a substring of 'abc'");
    };

    if (_ypython_string_count_sub_string("abc abc acbc", "abc") != 2) {
        ypython_print("'abc' should appeared 2 times in 'abc abc acbc'");
    };
}