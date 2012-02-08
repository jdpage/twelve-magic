/*
 * core.c
 *
 * Contains the definitions for all of the core words in the language.
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "core.h"

/*
 * (a b -- c)
 * c = a + b
 */
void native_add(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a + b));
}

/*
 * (a b -- c)
 * c = a - b
 */
void native_subtract(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a - b));
}

/*
 * (a b -- c)
 * c = a * b
 */
void native_multiply(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a * b));
}

/*
 * (a b -- c)
 * c = a / b
 */
void native_divide(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a / b));
}

/*
 * (a b -- c)
 * c = a mod b
 */
void native_modulo(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a % b));
}

/*
 * (a b -- rem quot)
 * rem = a mod b
 * quot = a / b
 */
void native_divmod(cons_t **stack, dict_t **scope) {
	long a, b;
	UNUSED(scope);
	b = unwrap_number(list_pop(stack));
	a = unwrap_number(list_pop(stack));
	list_push(stack, wrap_number(a % b));
	list_push(stack, wrap_number(a / b));
}

/*
 * (a --)
 * prints a to stdout followed by a space
 */
void native_print(cons_t **stack, dict_t **scope) {
	long a;
	UNUSED(scope);
	a = unwrap_number(list_pop(stack));
	printf("%ld", a);
}

/*
 * (a -- a a)
 */
void native_dup(cons_t **stack, dict_t **scope) {
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
void native_drop(cons_t **stack, dict_t **scope) {
	UNUSED(scope);
	list_pop(stack);
}

/*
 * (a --)
 * ends the process with code a
 */
void native_exit(cons_t **stack, dict_t **scope) {
	long a;
	UNUSED(scope);
	a = unwrap_number(list_pop(stack));
	exit(a);
}

/*
 * (a --)
 * prints out the ascii character corresponding to a
 * TODO: use utf-8
 */
void native_emit(cons_t **stack, dict_t **scope) {
	UNUSED(scope);
	printf("%c", (int)unwrap_number(list_pop(stack)));
}

/*
 * MACRO
 * The Big Daddy of all macros - the one that defines other macros.
 */
/* void nmacro_macro(cons_t **stack, dict_t **scope) {
	cons_t *macro, *macro_tail;
	value_t val;
	dict_t *semicolon;
	macro = NULL;
	macro_tail = NULL;
	const char *name;
	semicolon = dict_get(scope, ";");
	if (semicolon == NULL) {
		fprintf(stderr, "missing semicolon!");
		return;
	}
	val = list_pop(stack);
	name = dict_key(as_symbol(val));
	while (1) {
		val = list_pop(stack);
		if (symbol_p(val) && as_symbol(val) == semicolon)
			break;
		macro_tail = list_link(macro_tail, val);
		if (macro == NULL)
			macro = macro_tail;
	}
	dict_add(scope, name, mk_macro(mk_function(macro)));
} */

/*
 * MACRO (a --)
 * returns the pointer value of symbol a
 */
void nmacro_ref(cons_t **stack, dict_t **scope) {
	value_t v;
	dict_t *e;
	UNUSED(scope);

	v = list_pop(stack);
	if (symbol_p(v)) {
		e = unwrap_symbol(v);
		v = value(e);
		v.storage = S_LITERAL;
	}
	list_push(stack, v);
}

void native_call(cons_t **stack, dict_t **scope) {
	unwrap_native(list_pop(stack))(stack, scope);
}

void init_core() {
	core_scope = NULL;
	core_scope = dict_add(core_scope, "+", wrap_native(native_add));
	core_scope = dict_add(core_scope, "-", wrap_native(native_subtract));
	core_scope = dict_add(core_scope, "*", wrap_native(native_multiply));
	core_scope = dict_add(core_scope, "/", wrap_native(native_divide));
	core_scope = dict_add(core_scope, "mod", wrap_native(native_modulo));
	core_scope = dict_add(core_scope, "/mod", wrap_native(native_divmod));
	core_scope = dict_add(core_scope, ".", wrap_native(native_print));
	core_scope = dict_add(core_scope, "dup", wrap_native(native_dup));
	core_scope = dict_add(core_scope, "drop", wrap_native(native_drop));
	core_scope = dict_add(core_scope, "exit", wrap_native(native_exit));
	core_scope = dict_add(core_scope, "emit", wrap_native(native_emit));
	core_scope = dict_add(core_scope, "call", wrap_native(native_call));
	core_scope = dict_add(core_scope, "'", wrap_native(nmacro_ref));
	set_macro(core_scope, 1);
	/* core_scope = dict_add(core_scope, "!", mk_macro(wrap_native(nmacro_macro))); */
}
