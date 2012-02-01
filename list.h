#pragma once

typedef enum type {
	T_NONE,
	T_LITERAL,
	T_DATA,
	T_NATIVE,
	T_FUNCTION,
	T_NMACRO,
	T_FMACRO
} type_t;

typedef struct value {
	long numeric;
	type_t type;
} value_t;

typedef struct element {
	struct element *next;
	struct element *prev;
	value_t value;
} element_t;

typedef struct list {
	struct element *head;
	struct element *tail;
} list_t;

list_t *list_new();
void list_del(list_t *self);
void list_push(list_t *self, value_t val);
value_t list_pop(list_t *self);
value_t list_pop_head(list_t *self);
value_t list_peek(list_t *self);
value_t list_peek_head(list_t *self);
int list_empty_p(list_t *self);
unsigned long list_length(list_t *self);
void list_set(list_t *self, unsigned long index, value_t val);
value_t list_get(list_t *self, unsigned long index);
element_t *list_begin(list_t *self);
element_t *list_end(list_t *self);
element_t *next(element_t *self);
element_t *prev(element_t *self);
value_t get_value(element_t *self);

