#pragma once
#include "list.h"

typedef struct entry {
	struct entry *next;
	char *key;
	value_t value;
} entry_t;

typedef struct dict {
	struct entry *head;
	struct entry *cursor;
} dict_t;

dict_t *dict_new();
void dict_del(dict_t *self);
void dict_add(dict_t *self, const char *key, value_t val);
value_t dict_get(dict_t *self, const char *key);
void dict_attach(dict_t *self, dict_t *other);
