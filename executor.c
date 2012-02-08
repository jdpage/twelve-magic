/*
 * executor.c
 *
 * Contains the code which actually executes the programs. Also contains the
 * macro processor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "executor.h"

/*
 * ~~ a brief interlude about the executor ~~
 *
 * The executor takes a function, which is a list of values, the 
 * current stack, which it may modify, and a scope, which it will not modify.
 *
 * It uses the following algorithm to execute the function:
 * 1. Get the next value. if there are no more values, end.
 *   a. if the value is a number, push it onto the stack
 *   b. if the value is a function, call it with the current stack and scope
 *     1. if the function is a native, call it directly
 *     2. otherwise, call execute() on it
 * 2. Go to 1.
 */
void execute(cons_t *prog, cons_t **stack, dict_t **scope) {
	dict_t *symbol;
	value_t val;

	while (prog != NULL) {
		val = CAR(prog);
		if (number_p(val)) {
			list_push(stack, val);
		} else if (symbol_p(val)) {
			symbol = unwrap_symbol(val);
			val = value(symbol);
			if (null_p(val)) {
				fprintf(stderr, "%s? ", key(symbol));
				break;
			} else {
				unwrap_native(val)(stack, scope);
			}
		} else {
			printf("OH DANG BRO %d:%ld\n", val.storage, val.value.literal);
		}
		prog = list_next(prog);
	}
}

cons_t *do_macros(cons_t *rprog, dict_t **scope) {
	dict_t *symbol;
	value_t val;
	cons_t *stack = NULL;

	while (rprog != NULL) {
		val = list_peek(rprog);
		if (symbol_p(val) && macro_p(unwrap_symbol(val))) {
			symbol = unwrap_symbol(val);
			unwrap_native(value(symbol))(&stack, scope);
		} else {
			list_push(&stack, val);
		}
		rprog = list_next(rprog);
	}

	return stack;
}
