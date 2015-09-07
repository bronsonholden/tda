#ifndef TDA_MM_H
#define TDA_MM_H

#include <tda/mm/heap.h>
#include <tda/mm/pool.h>
#include <tda/mm/stack.h>

int mm_init(int argc, const char *argv[]);

void mm_deinit(void);

int mm_is_init(void);

#endif /* TDA_MM_H */
