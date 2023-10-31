#include "./y_python.h"


int test_number = 0;


void print_seperator(const char * test_name) {
    test_number += 1;
    ypython_print("\n---------------\n");
    if (_ypython_string_is_string_equal(test_name, "")) {
        _ypython_print_formated_string("Test %d", test_number);
    } else {
        _ypython_print_formated_string("Test %d: %s", test_number, test_name);
    }
    ypython_print("\n\n---------------\n");
}


int main()
{
    print_seperator("");

    const char *result = ypython_run_command("echo 'hi'");
    const char *new_result = ypython_string_strip((char *)result);
    if (_ypython_string_compare(new_result, "hi") != 0)
    {
        _ypython_print_formated_string("'hi' should equal to '%s'\n", new_result);
        exit(0);
    }

    ///////////////////////////////////////////////////////
    
    print_seperator("");

    ypython_run("uname -v");

    //////////////////////////////////////////////////////

    print_seperator("");

    _ypython_print_formated_string("Hi, '%s'.\n", "yingshaoxo");

    //////////////////////////////////////////////////////

    print_seperator("");

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

    print_seperator("");

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

    print_seperator("");

    Type_Ypython_String *a_string = Ypython_String("yingshaoxo");
    ypython_print(a_string->value);

    Type_Ypython_String *another_string = Ypython_String(" is super nice.");
    Type_Ypython_String *final_string = a_string->function_add(a_string, another_string);

    Type_Ypython_String *target_string = Ypython_String("yingshaoxo is super nice.");
    if (!(target_string->function_is_equal(target_string, final_string))) {
        //ypython_print(target_string->value);
        //ypython_print(final_string->value);
        _ypython_print_formated_string("'%s' should equal to '%s'\n", final_string->value, target_string->value);
    }

    //////////////////////////////////////////////////////

    print_seperator("");

    if (!_ypython_string_is_sub_string("abc", "ab")) {
        ypython_print("'ab' should be a substring of 'abc'");
    };

    if (_ypython_string_is_sub_string("abc", "ac")) {
        ypython_print("'ab' should not be a substring of 'abc'");
    };

    if (_ypython_string_count_sub_string("abc abc acbc", "abc") != 2) {
        ypython_print("'abc' should appeared 2 times in 'abc abc acbc'");
    };

    //////////////////////////////////////////////////////

    print_seperator("");

    a_string = Ypython_String("nice");
    if (!(a_string->function_is_equal(Ypython_String(a_string->type), Ypython_String("string")))) {
        ypython_print("type should be 'string'");
    }

    //////////////////////////////////////////////////////

    print_seperator("General Type");

    Type_Ypython_String *a_string_2 = Ypython_String("nice");

    Type_Ypython_General *general_variable = Ypython_General();
    general_variable->string_ = a_string_2;
    ypython_print(general_variable->string_->value);

    if (general_variable->string_->function_is_equal(general_variable->string_, Ypython_String("nice")) == false) {
        ypython_print("Error in general type");
    }
    
    //////////////////////////////////////////////////////
    
    print_seperator("List Test");

    Type_Ypython_List *a_list = Ypython_List();

    Type_Ypython_General *general_variable_2 = Ypython_General();
    Type_Ypython_String *a_string_3 = Ypython_String("element in list");
    general_variable_2->string_ = a_string_3;

    a_list = a_list->function_append(a_list, general_variable_2);
    ypython_print(a_list->value[0]->string_->value);

    a_list = a_list->function_delete(a_list, 0);
    a_list = a_list->function_insert(a_list, 0, general_variable_2);
    ypython_print(a_list->value[0]->string_->value);

    Type_Ypython_Int *index = a_list->function_index(a_list, general_variable_2);
    _ypython_print_formated_string("%lld\n", index->value);

    //////////////////////////////////////////////////////
    
    print_seperator("General type compare Test");

    Type_Ypython_General *general_variable_3 = Ypython_General();
    Type_Ypython_String *a_string_4 = Ypython_String("element in list");
    general_variable_3->string_ = a_string_4;

    Type_Ypython_General *general_variable_4 = Ypython_General();
    Type_Ypython_String *a_string_5 = Ypython_String("element in list");
    general_variable_4->string_ = a_string_5;

    if (general_variable_4->function_is_equal(general_variable_3, general_variable_4) == false) {
        ypython_print("Error in general type compare");
    }

    Type_Ypython_String *a_string_6 = Ypython_String("jilkjalsdhfkj in list");
    general_variable_4->string_ = a_string_6;

    if (general_variable_4->function_is_equal(general_variable_3, general_variable_4) == true) {
        ypython_print("Error in general type compare");
    }

    //////////////////////////////////////////////////////
    
    print_seperator("Dict Test");

    Type_Ypython_General *general_variable_7 = Ypython_General();
    Type_Ypython_String *a_string_7 = Ypython_String("yingshaoxo");
    general_variable_7->string_ = a_string_7;

    Type_Ypython_Dict *a_dict = Ypython_Dict();
    Type_Ypython_String *the_key_7 = Ypython_String("god");
    a_dict->function_set(a_dict, the_key_7, general_variable_7);

    Type_Ypython_General *general_variable_8 = a_dict->function_get(a_dict, the_key_7);
    ypython_print(general_variable_8->string_->value);
}
