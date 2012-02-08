/*
 * util.c
 *
 * Utility functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void panic(const char *msg) {
	fprintf(stderr, msg);
	abort();
}
