#include <stdio.h>
#include <string.h>
#include <physfs.h>
#include <tda/mm.h>
#include <tda/fs/vfs.h>

#define ENABLE_VFS_LOG 1

static const char *vfs[NUM_VFS_MOUNT_POINTS] = {
	"/core",
	"/var",
	"/etc"
	};

int vfs_mount(int point, const char *path)
{
	/* TODO: Make sure you can't trick PhysicsFS by passing a virtual
	 * file path to e.g. trick the unique VAR requirement.
	 */

	if (point < 0 || point >= NUM_VFS_MOUNT_POINTS)
		return 0;

	if (!PHYSFS_mount(path, vfs[point], 1))
		return 0;

	if (ENABLE_VFS_LOG)
		printf("vfs: mounted \"%s\" at \"%s\"\n", path, vfs[point]);

	return 1;
}
