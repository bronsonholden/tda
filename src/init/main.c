#include <stdio.h>
#include <tda/fs.h>
#include <tda/mm.h>
#include <tda/hid.h>
#include <tda/math.h>

int main(int argc, char *argv[])
{
	if (!mm_init(argc, argv))
		return 1;

	if (!fs_init(argc, argv))
		return 1;

	fs_deinit();
	mm_deinit();

	return 0;
}
