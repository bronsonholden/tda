#include <string.h>
#include <tda/mm/heap.h>
#include <tda/mm/stack.h>

#define ENABLE_STACK_LOG 1

#define DEFAULT_STACK_SIZE (1 << 28)

static void    *stack_buffer;
static void    *stack_marker;
static size_t   stack_size;
static size_t   stack_usage;

static int is_init;

int stack_init(int argc, const char *argv[])
{
	stack_buffer = heap_malloc(DEFAULT_STACK_SIZE);
	if (!stack_buffer)
		return 0;

	if (ENABLE_STACK_LOG)
		printf("stack: %dMB allocated\n", DEFAULT_STACK_SIZE >> 20);

	stack_usage   = 0;
	stack_size    = DEFAULT_STACK_SIZE;
	stack_marker  = stack_buffer;

	is_init = 1;

	return 1;
}

void stack_deinit(void)
{
	heap_free(stack_buffer);

	if (ENABLE_STACK_LOG) {
		if (stack_marker != stack_buffer) {
			printf("stack: marker expected 0x%X, got 0x%X\n",
			       stack_buffer, stack_marker);
		}

		printf("stack: released\n");
	}

	is_init = 0;
}

int stack_is_init(void)
{
	return is_init;
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
