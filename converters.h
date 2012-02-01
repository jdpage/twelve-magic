#pragma once
#include "dict.h"

typedef void (*native_t)(list_t *stack, dict_t *scope);

value_t mk_number(long n);
value_t mk_data(long *p);
value_t mk_native(native_t n);
value_t mk_function(list_t *f);
value_t mk_null();

int number_p(value_t v);
int data_p(value_t v);
int native_p(value_t v);
int function_p(value_t v);
int null_p(value_t v);
int macro_p(value_t v);
int fmacro_p(value_t v);
int nmacro_p(value_t v);

long as_number(value_t n);
long *as_data(value_t p);
native_t as_native(value_t n);
list_t *as_function(value_t f);

