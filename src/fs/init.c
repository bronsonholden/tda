#include <physfs.h>
#include <tda/fs.h>

static int is_init;

int fs_init(int argc, const char *argv[])
{
	if (!PHYSFS_init(argv[0]))
		return 0;

	PHYSFS_addToSearchPath(PHYSFS_getUserDir(), 0);

	PHYSFS_setWriteDir(PHYSFS_getUserDir());

	is_init = 1;

	return 1;
}

void fs_deinit(void)
{
	PHYSFS_deinit();

	is_init = 0;
}

int fs_is_init(void)
{
	return is_init;
}
