#pragma once
#include <stdio.h>
#include "dict.h"

int default_radix;
list_t *parse(FILE *fd, dict_t *scope, int break_on_newline);
