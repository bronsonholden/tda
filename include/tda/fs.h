#ifndef TDA_FS_H
#define TDA_FS_H

#include <tda/fs/file.h>
#include <tda/fs/vfs.h>

int fs_init(int argc, const char *argv[]);

void fs_deinit(void);

int fs_is_init(void);

#endif /* TDA_FS_H */
