#pragma once

/*
 * The different storage types. These are different from the actual types.
 * (Actually, there isn't a typing system yet. But when there is, the types
 * will be distinct from this. This is just talking about the internal
 * storage is.)
 */
typedef enum storage {
	S_NULL,    /* a null value */
	S_LITERAL, /* a literal value */
	S_POINTER, /* a pointer to data */
	S_SYMBOL,  /* a dictionary entry */
	S_CONS,    /* a cons cell */
	S_NATIVE   /* a native function */
} storage_t;

struct cons;
struct dict;

typedef void (*native_t)(struct cons **stack, struct dict **scope);

/*
 * A value. This sort of lets us pretend that C has templates.
 * The neat thing is that a long and the various pointer types usually fit into
 * the same space.
 */

typedef struct value {
	union {
		long literal;
		void *pointer;
		struct dict *symbol;
		struct cons *cons;
		native_t native;
	} value;
	storage_t storage;
} value_t;

/*
 * A cons cell. Basically a pair of values. Can be used to implement various
 * data structures.
 */
typedef struct cons {
	value_t first;
	value_t second;
} cons_t;

/*
 * A dictionary entry.
 */
typedef struct dict {
	struct dict *next;
	char *key;
	value_t value;
	int macro;
} dict_t;

/*
 * Value operations
 */
value_t wrap_number(long n);
value_t wrap_pointer(void *p);
value_t wrap_symbol(dict_t *s);
value_t wrap_cons(cons_t *c);
value_t wrap_native(native_t f);
value_t null();
int number_p(value_t v);
int pointer_p(value_t v);
int symbol_p(value_t v);
int cons_p(value_t v);
int native_p(value_t v);
int null_p(value_t v);
long unwrap_number(value_t n);
void *unwrap_pointer(value_t p);
dict_t *unwrap_symbol(value_t s);
cons_t *unwrap_cons(value_t c);
native_t unwrap_native(value_t f);

/*
 * Cons operations.
 */
cons_t *cons(value_t first, value_t second);
void cons_del(cons_t *cell);
value_t *car(cons_t *cell);
value_t *cdr(cons_t *cell);
cons_t *cons_clone(cons_t *cell);

/* one-letter */
#define CAR(cell) *car(cell)
#define CDR(cell) *cdr(cell)

/* two-letter */
#define CAAR(cell) CAR(CAR(cell))
#define CADR(cell) CAR(CDR(cell))
#define CDAR(cell) CDR(CAR(cell))
#define CDDR(cell) CDR(CDR(cell))

/* three-letter */
#define CAAAR(cell) CAAR(CAR(cell))
#define CAADR(cell) CAAR(CDR(cell))
#define CADAR(cell) CADR(CAR(cell))
#define CADDR(cell) CADR(CDR(cell))
#define CDAAR(cell) CDAR(CAR(cell))
#define CDADR(cell) CDAR(CDR(cell))
#define CDDAR(cell) CDDR(CAR(cell))
#define CDDDR(cell) CDDR(CDR(cell))

/* four-letter */
#define CAAAAR(cell) CAAAR(CAR(cell))
#define CAAADR(cell) CAAAR(CDR(cell))
#define CAADAR(cell) CAADR(CAR(cell))
#define CAADDR(cell) CAADR(CDR(cell))
#define CADAAR(cell) CADAR(CAR(cell))
#define CADADR(cell) CADAR(CDR(cell))
#define CADDAR(cell) CADDR(CAR(cell))
#define CADDDR(cell) CADDR(CDR(cell))
#define CDAAAR(cell) CDAAR(CAR(cell))
#define CDAADR(cell) CDAAR(CDR(cell))
#define CDADAR(cell) CDADR(CAR(cell))
#define CDADDR(cell) CDADR(CDR(cell))
#define CDDAAR(cell) CDDAR(CAR(cell))
#define CDDADR(cell) CDDAR(CDR(cell))
#define CDDDAR(cell) CDDDR(CAR(cell))
#define CDDDDR(cell) CDDDR(CDR(cell))

/*
 * Linked list operations (implemented using cons cells)
 */
value_t list_pop(cons_t **head);
void list_push(cons_t **head, value_t item);
void list_free(cons_t *head);
cons_t *list_next(cons_t *cell);
cons_t *list_link(cons_t *cell, value_t item);
value_t list_peek(cons_t *cell);
int list_p(cons_t *cell);
int list_empty_p(cons_t *head);
unsigned long list_length(cons_t *head);
void list_print(cons_t *head);
cons_t *list_reverse_destructive(cons_t *head);
cons_t *list_clone(cons_t *head);

/*
 * Dictionary operations (implemented using entries)
 */
const char *key(dict_t *entry);
value_t value(dict_t *entry);
dict_t *dict_add(dict_t *head, const char *key, value_t value);
dict_t *dict_get(dict_t *head, const char *key);
dict_t *dict_forget(dict_t *head, const char *key);
int macro_p(dict_t *entry);
void set_macro(dict_t *entry, int state);

