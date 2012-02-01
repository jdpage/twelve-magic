#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "converters.h"
#include "core.h"

/*
 * (a b -- c)
 * c = a + b
 */
void native_add(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a + b));
}

/*
 * (a b -- c)
 * c = a - b
 */
void native_subtract(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a - b));
}

/*
 * (a b -- c)
 * c = a * b
 */
void native_multiply(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a * b));
}

/*
 * (a b -- c)
 * c = a / b
 */
void native_divide(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a / b));
}

/*
 * (a b -- c)
 * c = a mod b
 */
void native_modulo(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a % b));
}

/*
 * (a b -- rem quot)
 * rem = a mod b
 * quot = a / b
 */
void native_divmod(list_t *stack, dict_t *scope) {
	long a, b;
	UNUSED(scope);
	b = as_number(list_pop(stack));
	a = as_number(list_pop(stack));
	list_push(stack, mk_number(a % b));
	list_push(stack, mk_number(a / b));
}

/*
 * (a --)
 * prints a to stdout followed by a space
 */
void native_print(list_t *stack, dict_t *scope) {
	long a;
	UNUSED(scope);
	a = as_number(list_pop(stack));
	printf("%ld", a);
}

/*
 * (a -- a a)
 */
void native_dup(list_t *stack, dict_t *scope) {
	value_t v;
	UNUSED(scope);
	v = list_pop(stack);
	list_push(stack, v);
	list_push(stack, v);
}

/*
 * (a --)
 * no side-effects
 */
void native_drop(list_t *stack, dict_t *scope) {
	UNUSED(scope);
	list_pop(stack);
}

/*
 * (a --)
 * ends the process with code a
 */
void native_exit(list_t *stack, dict_t *scope) {
	long a;
	UNUSED(scope);
	a = as_number(list_pop(stack));
	exit(a);
}

/*
 * (a --)
 * prints out the ascii character corresponding to a
 * TODO: use utf-8
 */
void native_emit(list_t *stack, dict_t *scope) {
	UNUSED(scope);
	printf("%c", (int)as_number(list_pop(stack)));
}

void init_core() {
	core_scope = dict_new();
	dict_add(core_scope, "+", mk_native(native_add));
	dict_add(core_scope, "-", mk_native(native_subtract));
	dict_add(core_scope, "*", mk_native(native_multiply));
	dict_add(core_scope, "/", mk_native(native_divide));
	dict_add(core_scope, "mod", mk_native(native_modulo));
	dict_add(core_scope, "/mod", mk_native(native_divmod));
	dict_add(core_scope, ".", mk_native(native_print));
	dict_add(core_scope, "dup", mk_native(native_dup));
	dict_add(core_scope, "drop", mk_native(native_drop));
	dict_add(core_scope, "exit", mk_native(native_exit));
	dict_add(core_scope, "emit", mk_native(native_emit));
}
