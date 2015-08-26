#include <string.h>
#include <tda/mm/heap.h>
#include <tda/mm/stack.h>

#define DEFAULT_STACK_SIZE (1 << 28)

static void    *stack_buffer;
static void    *stack_marker;
static size_t   stack_size;
static size_t   stack_usage;

int stack_init(void)
{
	stack_buffer = heap_malloc(DEFAULT_STACK_SIZE);
	if (!stack_buffer)
		return 0;

	stack_usage   = 0;
	stack_size    = DEFAULT_STACK_SIZE;
	stack_marker  = stack_buffer;

	return 1;
}

int stack_deinit(void)
{
	heap_free(stack_buffer);

	return 1;
}

void *stack_malloc(size_t sz)
{
	ptrdiff_t tmp;
	void *ptr;

	if (!stack_buffer || stack_usage + sz > stack_size)
		return 0;

	ptr = stack_marker;

	tmp = (ptrdiff_t)stack_marker;
	tmp = tmp + sz;

	stack_marker = (void *) tmp;

	stack_usage += sz;

	return ptr;
}

void *stack_calloc(size_t num, size_t sz)
{
	void *ptr;

	sz *= num;

	ptr = stack_malloc(sz);
	if (!ptr)
		return 0;

	return memset(ptr, 0, sz);
}

void *stack_realloc(void *ptr, size_t sz)
{
	size_t tmp;

	if (!ptr && sz)
		return stack_malloc(sz);

	if (ptr && !sz) {
		stack_free(ptr);

		return 0;
	}

	if (ptr > stack_marker)
		return 0;

	tmp = (size_t)((ptrdiff_t)stack_marker - (ptrdiff_t)ptr);

	if (sz > tmp) {
		/* Request extra bytes to realloc to a larger size */
		if (!stack_malloc(sz - tmp))
			return 0;
	} else {
		/* Roll back stack marker to realloc to a smaller size */
		stack_marker = (void *)((ptrdiff_t)stack_marker + (ptrdiff_t)sz);
	}

	return ptr;
}

void stack_free(void *ptr)
{
	if (!ptr)
		return;

	stack_usage -= ((ptrdiff_t)stack_marker - (ptrdiff_t)ptr);

	stack_marker = ptr;
}