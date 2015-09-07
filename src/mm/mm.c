#include <tda/mm.h>

static int is_init;

int mm_init(int argc, const char *argv[])
{
	if (!heap_init(argc, argv))
		goto err;

	if (!stack_init(argc, argv))
		goto err;

	if (!pool_init(argc, argv))
		goto err;

	is_init = 1;

	return 1;
err:
	mm_deinit();

	return 0;
}

void mm_deinit(void)
{
	if (pool_is_init())
		pool_deinit();

	if (stack_is_init())
		stack_deinit();

	if (heap_is_init())
		heap_deinit();

	is_init = 0;
}

int mm_is_init(void)
{
	return is_init;
}
