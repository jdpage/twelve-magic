#include <stdio.h>
#include "config.h"
#include "util.h"
#include "core.h"
#include "converters.h"
#include "parser.h"
#include "executor.h"

int main(int argc, char **argv) {
	list_t *line, *stack;
	unsigned long count = 0;

	UNUSED(argc);
	UNUSED(argv);

	default_radix = DEFAULT_RADIX;

	printf("Twelve Magic (version %04d.%02d.%02d%c)\n", VERSION_YEAR, VERSION_MONTH, VERSION_DAY, VERSION_MINOR);

	init_core();
	stack = list_new();

	while (1) {
		printf("%lu ~ ", count++);
		line = parse(stdin, core_scope, 1);
		if (line == NULL)
			continue;
		execute(line, stack, core_scope); 
		printf(" (ok) ");
	}

	return 0;
}
