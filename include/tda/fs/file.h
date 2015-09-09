#ifndef TDA_FS_FILE_H
#define TDA_FS_FILE_H

enum FILE_MODE
{
	FILE_MODE_READONLY,
	FILE_MODE_READWRITE,
	FILE_MODE_APPEND
};

enum FILE_SEEK
{
	FILE_SEEK_SET,
	FILE_SEEK_CUR,
	FILE_SEEK_END
};

typedef struct file file_t;

file_t *file_open(const char *filename, int mode);

void file_close(file_t *file);

int file_read(file_t *file, char *dest, int num);

int file_write(file_t *file, const char *src, int num);

/* Return non-zero if the file pointer is at the end-of-file mark.
 */
int file_eof(file_t *file);

/* Set the file pointer to a given position. Returns non-zero on success,
 * zero on failure.
 */
int file_seek(file_t *file, int offset, int whence);

#endif /* TDA_FS_FILE_H */
