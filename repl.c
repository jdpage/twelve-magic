#include <stdio.h>
#include "config.h"
#include "util.h"
#include "data.h"
#include "core.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char **argv) {
	cons_t *line, *stack = NULL, *prog;
	unsigned long count = 0;
	/* element_t *iter;
	entry_t *e;
	value_t v; */

	UNUSED(argc);
	UNUSED(argv);

	default_radix = DEFAULT_RADIX;

	printf("Twelve Magic (version %04d.%02d.%02d%c)\n", VERSION_YEAR, VERSION_MONTH, VERSION_DAY, VERSION_MINOR);

	init_core();

	while (1) {
		printf("%lu ~> ", count++);
		line = parse(stdin, &core_scope, 1);
		if (line == NULL)
			continue;
		prog = do_macros(line, &core_scope);
		/* fprintf(stderr, " [");
		for (iter = list_end(line); iter != NULL; iter = prev(iter)) {
			v = get_value(iter);
			if (number_p(v)) {
				fprintf(stderr, "%ld ", as_number(v));
			} else {
				e = as_symbol(v);
				fprintf(stderr, "%s", dict_key(e));
				if (null_p(dict_value(e))) {
					fprintf(stderr, "?");
				}
				fprintf(stderr, " ");
			}
		}
		fprintf(stderr, "] "); */
		execute(prog, &stack, &core_scope); 
		printf(" (ok) ");
		list_free(line);
		list_free(prog);
	}

	return 0;
}
