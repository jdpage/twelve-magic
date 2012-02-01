#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "converters.h"
#include "dict.h"

dict_t *dict_new() {
	dict_t *self;

	SAFE(self = NEW(dict_t));
	self->head = NULL;
	self->cursor = NULL;

	return self;
}

void dict_del(dict_t *self) {
	entry_t *curr, *next;

	curr = self->head;

	while (curr != self->cursor) {
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(self->cursor);
	free(self);
}

void dict_add(dict_t *self, const char *key, value_t val) {
	entry_t *e;

	SAFE(e = NEW(entry_t));
	SAFE(e->key = MAKE(char, strlen(key) + 1));
	strcpy(e->key, key);
	e->value = val;

	if (self->head == NULL && self->cursor == NULL) {
		/* empty dict */
		self->head = e;
		self->cursor = e;
		e->next = NULL;
	} else if (self->head != NULL && self->cursor == NULL) {
		/* empty dict with another dict attached */
		e->next = self->head;
		self->head = e;
		self->cursor = e;
	} else {
		/* normal case */
		e->next = self->cursor->next;
		self->cursor->next = e;
		self->cursor = e;
	}
}

value_t dict_get(dict_t *self, const char *key) {
	entry_t *e;

	e = self->head;

	while (e != NULL && strcmp(e->key, key) != 0) {
		e = e->next;
	}

	if (e == NULL)
		return mk_null();

	return e->value;
}

void dict_attach(dict_t *self, dict_t *other) {
	if (self->head == NULL) {
		self->head = other->head;
	} else {
		self->cursor->next = other->head;
	}
}
