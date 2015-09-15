#ifndef TDA_FS_VFS_H
#define TDA_FS_VFS_H

enum VFS_MOUNT
{
	/* Contains engine resources such as shaders, meshes, etc. */
	VFS_MOUNT_CORE,
	/* Write directory for the application during runtime. */
	VFS_MOUNT_VAR,
	/* Contains engine configuration files */
	VFS_MOUNT_ETC,
	NUM_VFS_MOUNT_POINTS
};

/* Mount a directory to a given mount point. Multiple directories can be
 * mounted to the same mount point, but if any file opened exists in both
 * real directories, the one from the most-recently mounted is opened.
 * A single directory cannot be mounted to more than one mount point.
 * Returns non-zero on success, zero on failure.
 */
int vfs_mount(int point, const char *path);

#endif /* TDA_FS_VFS_H */
