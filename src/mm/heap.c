#include <malloc.h>
#include <tda/mm/heap.h>

int heap_init(void)
{
	return 1;
}

int heap_deinit(void)
{
	return 1;
}

void *heap_malloc(size_t sz)
{
	return malloc(sz);
}

void *heap_calloc(size_t num, size_t sz)
{
	return calloc(num, sz);
}

void *heap_realloc(void *ptr, size_t sz)
{
	return realloc(ptr, sz);
}

void heap_free(void *ptr)
{
	free(ptr);
}
