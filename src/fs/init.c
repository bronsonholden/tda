#include <string.h>
#include <physfs.h>
#include <tda/fs.h>
#include <tda/mm.h>

static int is_init;

/* Puts a concatenation of a base and subdirectory onto stack memory, returning
 * a pointer on success.
 */
static char *strdir(const char *base, const char *dir)
{
	char *str;
	int len1, len2;

	len1 = strlen(base);
	len2 = strlen(dir);

	if (len1 < 1 || len2 < 1)
		return 0;

	/* Allocate additional space for TDA and a null-terminator */
	str = stack_malloc(len1 + len2);
	if (!str)
		return 0;

	strcpy(str, base);
	strcpy(str + len1, dir);

	return str;
}

static int etc_init(void)
{
	const char *dir;
	char *str;
	int tmp;

	str = strdir(PHYSFS_getUserDir(), "TDA");
	if (!str)
		return 0;

	dir = PHYSFS_getWriteDir();

	PHYSFS_setWriteDir(PHYSFS_getUserDir());

	if (!PHYSFS_isDirectory("TDA"))
		PHYSFS_mkdir("TDA");

	PHYSFS_setWriteDir(dir);

	tmp = vfs_mount(VFS_MOUNT_ETC, str);

	stack_free(str);

	return tmp;
}

static int var_init(void)
{
	const char *dir;
	char *str;
	int tmp;

	str = strdir(PHYSFS_getBaseDir(), "var");
	if (!str)
		return 0;

	dir = PHYSFS_getWriteDir();

	PHYSFS_setWriteDir(PHYSFS_getBaseDir());

	if (!PHYSFS_isDirectory("var"))
		PHYSFS_mkdir("var");

	PHYSFS_setWriteDir(dir);

	tmp = vfs_mount(VFS_MOUNT_VAR, str);

	stack_free(str);

	return tmp;
}

int fs_init(int argc, const char *argv[])
{
	if (!PHYSFS_init(argv[0]))
		return 0;

	if (!PHYSFS_mount(PHYSFS_getUserDir(), "/", 0))
		return 0;

	if (!etc_init())
		return 0;

	if (!var_init())
		return 0;

	PHYSFS_setWriteDir(PHYSFS_getRealDir("/var"));

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
