#pragma once

#define ERR_OUT_OF_MEMORY "ran out of memory!"

#define NEW(type) (type *)malloc(sizeof(type))
#define MAKE(type, size) (type *)malloc(sizeof(type) * (size))
#define SAFE(expr) if ((expr) == NULL) panic(ERR_OUT_OF_MEMORY)

void panic(const char *msg);

#define UNUSED(var) (void)var
