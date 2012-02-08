/*
 * executor.h
 *
 * Function prototypes for executor.c
 */

#pragma once
#include "data.h"

void execute(cons_t *prog, cons_t **stack, dict_t **scope);
cons_t *do_macros(cons_t *rprog, dict_t **scope);
