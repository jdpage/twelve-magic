/*
 * parser.h
 *
 * Contains function prototypes for parser.c
 */

#pragma once
#include <stdio.h>
#include "data.h"

int default_radix;
cons_t *parse(FILE *fd, dict_t **scope, int break_on_newline);
