#include <stdlib.h>
#include "util.h"
#include "data.h"

cons_t *cons(value_t first, value_t second) {
	cons_t *cell;
	SAFE(cell = NEW(cons_t));
	cell->first = first;
	cell->second = second;

	return cell;
}

cons_t *cons_clone(cons_t *cell) {
	if (cell == NULL)
		return NULL;
	return cons(CAR(cell), CDR(cell));
}

void cons_del(cons_t *cell) {
	free(cell);
}

value_t *car(cons_t *cell) {
	return &(cell->first);
}

value_t *cdr(cons_t *cell) {
	return &(cell->second);
}

