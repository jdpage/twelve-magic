#include <stdio.h>
#include <stdlib.h>
#include "data.h"

value_t list_pop(cons_t **head) {
	value_t val;
	cons_t *next;
	val = CAR(*head);
	next = list_next(*head);

	cons_del(*head);

	*head = next;
	return val;
}

void list_push(cons_t **head, value_t item) {
	cons_t *cell;
	value_t next;
	if (*head == NULL)
		next = null();
	else
		next = wrap_cons(*head);
	cell = cons(item, next);
	*head = cell;
}

void list_free(cons_t *head) {
	cons_t *cell;
	while (head != NULL) {
		cell = list_next(head);
		cons_del(head);
		head = cell;
	}
}

cons_t *list_next(cons_t *cell) {
	if (cell == NULL)
		return NULL;
	return unwrap_cons(CDR(cell));
}

cons_t *list_link(cons_t *cell, value_t item) {
	cons_t *tail;
	tail = cons(item, null());
	if (cell != NULL)
		CDR(cell) = wrap_cons(tail);
	return tail;
}

value_t list_peek(cons_t *cell) {
	if (cell == NULL)
		return null();
	return CAR(cell);
}

int list_p(cons_t *cell) {
	return cell == NULL || cons_p(CDR(cell));
}

int list_empty_p(cons_t *cell) {
	return cell == NULL;
}

unsigned long list_length(cons_t *head) {
	unsigned long length = 0;
	while (head != NULL) {
		head = list_next(head);
		length++;
	}
	return length;
}

void list_print(cons_t *head) {
	while (head != NULL) {
		fprintf(stdout, "%ld ", unwrap_number(CAR(head)));
		head = list_next(head);
	}
	fprintf(stdout, "\n");
	fflush(stdout);
}

cons_t *list_reverse_destructive(cons_t *head) {
	cons_t *next, *previous;
	previous = NULL;
	while (head != NULL) {
		next = unwrap_cons(CDR(head));
		CDR(head) = wrap_cons(previous);
		previous = head;
		head = next;
	}
	return previous;
}

cons_t *list_clone(cons_t *head) {
	cons_t *clone;
	head = cons_clone(head);
	clone = head;

	while (clone != NULL) {
		CDR(clone) = wrap_cons(cons_clone(unwrap_cons(CDR(clone))));
		clone = unwrap_cons(CDR(clone));
	}

	return head;
}
