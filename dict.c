#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "data.h"

const char *key(dict_t *entry) {
	return entry->key;
}

value_t value(dict_t *entry) {
	return entry->value;
}

dict_t *dict_add(dict_t *head, const char *key, value_t value) {
	dict_t *entry;
	SAFE(entry = NEW(dict_t));
	SAFE(entry->key = MAKE(char, strlen(key) + 1));
	strcpy(entry->key, key);
	entry->value = value;
	entry->next = head;
	return entry;
}

dict_t *dict_get(dict_t *head, const char *key) {
	while (head != NULL && strcmp(head->key, key) != 0) {
		head = head->next;
	}

	/* did we find anything? */
	if (head == NULL)
		return NULL;

	return head;
}

dict_t *dict_forget(dict_t *head, const char *key) {
	dict_t *prev = NULL, *curr = head;

	while (curr != NULL && strcmp(curr->key, key) != 0) {
		prev = curr;
		curr = curr->next;
	}

	/* did we find anything? */
	if (curr == NULL)
		return NULL;

	/* are we at the beginning of the list? */
	if (prev == NULL) {
		head = curr->next;
		free(curr);
		return head;
	}

	/* we're somewhere in the list */
	prev->next = curr->next; /* relink */
	free(curr);
	return head;
}

