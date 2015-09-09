#include <physfs.h>
#include <tda/mm.h>
#include <tda/fs/file.h>

struct file
{
	PHYSFS_file *file;
};

file_t *file_open(const char *filename, int mode)
{
	PHYSFS_file *f;
	file_t *file;

	switch (mode) {
	case FILE_MODE_READONLY:
		f = PHYSFS_openRead(filename);
		break;
	case FILE_MODE_READWRITE:
		f = PHYSFS_openWrite(filename);
		break;
	case FILE_MODE_APPEND:
		f = PHYSFS_openAppend(filename);
		break;
	default:
		f = 0;
	}

	if (!f)
		return 0;

	file = pool_malloc(sizeof(*file));
	if (!file) {
		PHYSFS_close(f);

		return 0;
	}

	file->file = f;

	return file;
}

void file_close(file_t *file)
{
	PHYSFS_close(file->file);

	pool_free(file);
}

int file_read(file_t *file, char *dest, int num)
{
	PHYSFS_sint64 tmp;

	tmp = PHYSFS_read(file->file, dest, 1, num);

	if (tmp < 0)
		return -1;

	return (int)tmp;
}

int file_write(file_t *file, const char *src, int num)
{
	PHYSFS_sint64 tmp;

	tmp = PHYSFS_write(file->file, src, 1, num);

	if (tmp < 0)
		return -1;

	return (int)tmp;
}

int file_eof(file_t *file)
{
	if (PHYSFS_eof(file->file))
		return 1;
	else
		return 0;
}

int file_seek(file_t *file, int offset, int whence)
{
	PHYSFS_sint64 tmp;
	int err;

	tmp = PHYSFS_tell(file->file);

	switch (whence) {
	case FILE_SEEK_SET:
		err = PHYSFS_seek(file->file, offset < 0 ? 0 : offset);

		break;
	case FILE_SEEK_CUR:
		tmp += offset;

		err = PHYSFS_seek(file->file, tmp < 0 ? 0 : tmp);

		break;
	case FILE_SEEK_END:
		/* Don't allow seeking end of file for now. Use file_read()
		 * in a loop until the EOF is encountered.
		 */
		return 0;
	default:
		return 0;
	}

	return err ? 1 : 0;
}
