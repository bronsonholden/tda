#ifndef TDA_MM_STACK_H
#define TDA_MM_STACK_H

#include <stddef.h>

struct stack_allocator
{
	void    *buffer;
	void    *marker;
	size_t   size;
};

int stack_init(int argc, const char *argv[]);

void stack_deinit(void);

int stack_is_init(void);

void *stack_malloc(size_t sz);

void *stack_calloc(size_t num, size_t sz);

void *stack_realloc(void *ptr, size_t sz);

void stack_free(void *ptr);

#endif /* TDA_MM_STACK_H */
