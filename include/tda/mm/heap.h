#ifndef TDA_MM_HEAP_H
#define TDA_MM_HEAP_H

#include <stddef.h>

int heap_init(void);

int heap_deinit(void);

void *heap_malloc(size_t sz);

void *heap_calloc(size_t num, size_t sz);

void *heap_realloc(void *ptr, size_t sz);

void heap_free(void *ptr);

#endif /* TDA_MM_HEAP_H */
