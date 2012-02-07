#pragma once
#include "data.h"

void execute(cons_t *prog, cons_t **stack, dict_t **scope);
void do_macros(cons_t **rprog, dict_t **scope);
