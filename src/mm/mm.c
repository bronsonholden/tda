#include <tda/mm.h>

int mm_init(void)
{
	if (!heap_init())
		return 0;

	if (!stack_init())
		return 0;

	if (!pool_init())
		return 0;

	return 1;
}

int mm_deinit(void)
{
	pool_deinit();
	stack_deinit();
	heap_deinit();

	return 1;
}
