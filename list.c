#include <stdlib.h>
#include "util.h"
#include "list.h"

list_t *list_new() {
	list_t *self;

	SAFE(self = NEW(list_t));
	self->head = NULL;
	self->tail = NULL;

	return self;
}

void list_del(list_t *self) {
	element_t *curr, *next;

	curr = self->head;

	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(self);
}

void list_push(list_t *self, value_t val) {
	element_t *item;

	SAFE(item = NEW(element_t));
	item->value = val;
	item->prev = self->tail;

	if (list_empty_p(self)) {
		self->head = item;
	} else {
		self->tail->next = item;
	}
	
	self->tail = item;
}

value_t list_pop(list_t *self) {
	value_t value;

	value = self->tail->value;
	self->tail = self->tail->prev;
	if (self->tail == NULL) {
		free(self->head);
		self->head = NULL;
	} else {
		free(self->tail->next);
		self->tail->next = NULL;
	}

	return value;
}

value_t list_pop_head(list_t *self) {
	value_t value;

	value = self->head->value;
	self->head = self->head->next;
	free(self->head->prev);
	self->head->prev = NULL;

	return value;
}

value_t list_peek(list_t *self) {
	return self->tail->value;
}

value_t list_peek_head(list_t *self) {
	return self->head->value;
}

int list_empty_p(list_t *self) {
	return self->head == NULL;
}

unsigned long list_length(list_t *self) {
	unsigned long length = 0;
	element_t *item;

	item = self->head;

	while (item != NULL) {
		length++;
		item = item->next;
	}

	return length;
}

void list_set(list_t *self, unsigned long index, value_t val) {
	element_t *item;
	item = self->head;

	while (index --> 0) {
		item = item->next;
	}

	item->value = val;
}

value_t list_get(list_t *self, unsigned long index) {
	element_t *item;
	item = self->head;

	while (index --> 0) {
		item = item->next;
	}

	return item->value;
}

element_t *list_begin(list_t *self) {
	return self->head;
}

element_t *list_end(list_t *self) {
	return self->tail;
}

element_t *next(element_t *self) {
	return self->next;
}

element_t *prev(element_t *self) {
	return self->prev;
}

value_t get_value(element_t *self) {
	return self->value;
}
