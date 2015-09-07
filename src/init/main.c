#include <stdio.h>
#include <string.h>
#include <tda/mm.h>
#include <tda/hid.h>

int main(int argc, char *argv[])
{
	hid_t *hid;
	struct hid_io io;

	if (!mm_init(argc, argv))
		return 1;

	hid = hid_create(0);
	if (!hid)
		printf("hid_create() failed\n");

	while (hid_poll(hid, 0, 0)) {
		hid_clear(hid, HID_CHANNEL_SCREEN);
		hid_flush(hid, HID_CHANNEL_SCREEN);

		while (hid_poll(hid, &io, HID_USER_INPUT_CHANNELS))
			;
	}

	hid_destroy(hid);

	mm_deinit();

	return 0;
}
