#include "converters.h"

value_t mk_number(long n) {
	value_t v = { .numeric = n, .type = T_LITERAL };
	return v;
}

value_t mk_data(long *p) {
	value_t v = { .numeric = (long)p, .type = T_DATA };
	return v;
}

value_t mk_native(native_t n) {
	value_t v = { .numeric = (long)n, .type = T_NATIVE };
	return v;
}

value_t mk_function(list_t *f) {
	value_t v = { .numeric = (long)f, .type = T_FUNCTION };
	return v;
}

value_t mk_null() {
	value_t v = { .numeric = 0, .type = T_NONE };
	return v;
}

int number_p(value_t v) {
	return v.type == T_LITERAL;
}

int data_p(value_t v) {
	return v.type == T_DATA;
}

int native_p(value_t v) {
	return v.type == T_NATIVE;
}

int function_p(value_t v) {
	return v.type == T_FUNCTION;
}

int null_p(value_t v) {
	return v.type == T_NONE;
}

int macro_p(value_t v) {
	return v.type == T_FMACRO || v.type == T_NMACRO;
}

int fmacro_p(value_t v) {
	return v.type == T_FMACRO;
}

int nmacro_p(value_t v) {
	return v.type == T_NMACRO;
}

long as_number(value_t n) {
	return n.numeric;
}

long *as_data(value_t p) {
	return (long *)p.numeric;
}

native_t as_native(value_t n) {
	return (native_t)n.numeric;
}

list_t *as_function(value_t f) {
	return (list_t *)f.numeric;
}
