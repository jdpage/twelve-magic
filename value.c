/*
 * value.c
 *
 * Implements basic value operations.
 */

#include "data.h"

value_t wrap_number(long n) {
	value_t v = { .value.literal = n, .storage = S_LITERAL };
	return v;
}

value_t wrap_pointer(void *p) {
	value_t v = { .value.pointer = p, .storage = S_POINTER };
	return v;
}

value_t wrap_symbol(dict_t *s) {
	value_t v = { .value.symbol = s, .storage = S_SYMBOL };
	return v;
}

value_t wrap_cons(cons_t *c) {
	value_t v = { .value.cons = c, .storage = S_CONS };
	return v;
}

value_t wrap_native(native_t f) {
	value_t v = { .value.native = f, .storage = S_NATIVE };
	return v;
}

value_t null() {
	value_t v = { .value.literal = 0, .storage = S_NULL };
	return v;
}

int number_p(value_t v)  { return v.storage == S_LITERAL; }
int pointer_p(value_t v) { return v.storage == S_POINTER; }
int symbol_p(value_t v)  { return v.storage == S_SYMBOL;  }
int cons_p(value_t v)    { return v.storage == S_CONS;    }
int native_p(value_t v)  { return v.storage == S_NATIVE;  }
int null_p(value_t v)    {
	return v.storage == S_NULL || (v.storage != S_LITERAL && v.value.literal == 0);
}

long unwrap_number(value_t n) {
	return n.value.literal;
}

void *unwrap_pointer(value_t p) {
	return p.value.pointer;
}

dict_t *unwrap_symbol(value_t s) {
	return s.value.symbol;
}

cons_t *unwrap_cons(value_t c) {
	return c.value.cons;
}

native_t unwrap_native(value_t f) {
	return f.value.native;
}

