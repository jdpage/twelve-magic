#include <stdlib.h>
#include "converters.h"
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
void execute(list_t *function, list_t *stack, dict_t *scope) {
	element_t *iter;
	value_t val;

	for (iter = list_begin(function); iter != NULL; iter = next(iter)) {
		val = get_value(iter);

		if (number_p(val)) {
			list_push(stack, val);
		} else {
			if (native_p(val)) {
				as_native(val)(stack, scope);
			} else {
				execute(as_function(val), stack, scope);
			}
		}
	}
}
