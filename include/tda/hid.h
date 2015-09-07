#ifndef TDA_HID_H
#define TDA_HID_H

typedef struct hid hid_t;

#define HID_CHANNEL_SCREEN          0x01
#define HID_CHANNEL_KEYBOARD        0x02
#define HID_CHANNEL_MOUSE           0x04

#define HID_ALL_CHANNELS            0xFF

#define HID_USER_INPUT_CHANNELS         \
	(                               \
	HID_CHANNEL_KEYBOARD          | \
	HID_CHANNEL_MOUSE             | \
	0                               \
	)

enum HID_IO_TYPE
{
	HID_IO_SCREEN,
	HID_IO_KEYBOARD,
	HID_IO_MOUSE,
};

enum HID_MOUSE_IO_SUBTYPE
{
	HID_MOUSE_IO_MOTION,
	HID_MOUSE_IO_BUTTON
};

struct hid_format
{
	int default_width;
	int default_height;
	int red_bits;
	int blue_bits;
	int green_bits;
	int alpha_bits;
	int depth_bits;
	int stencil_bits;
};

struct hid_io_screen
{
	int resize_x;
	int resize_y;
};

struct hid_io_keyboard
{
	int key;
	int scan_code;
	int pressed;
};

struct hid_io_mouse
{
	short subtype;
	short button;
	short pressed;
	short x;
	short y;
	short dx;
	short dy;
};

struct hid_io
{
	int type;
	union
	{
		struct hid_io_screen       screen;
		struct hid_io_keyboard     keyboard;
		struct hid_io_mouse        mouse;
	};
};

int hid_init(int argc, const char *argv[]);

void hid_deinit(void);

int hid_is_init(void);

/* Allocates and initializes a HID with the requested format. If
 * any error occurs, zero is returned. The returned pointer can be
 * passed to hid_destroy() to do clean-up and deallocation of memory.
 */
hid_t *hid_create(const struct hid_format *fmt);

/* Destroy a device returned from hid_create() and free any allocated
 * memory.
 */
void hid_destroy(hid_t *hid);

/* Clears any pending I/O for the HID. To avoid discarding input events,
 * call this only after polling returns zero for the corresponding
 * channels. For screen output, this simply clears the screen back-buffer.
 */
int hid_clear(hid_t *hid, int mask);

/* Flush any posted channel updates or changes. For screen output, this
 * swaps the front- and back-buffers then does any device changes such as
 * resizes. For user input channels, this is a no-op.
 */
int hid_flush(hid_t *hid, int mask);

/* Poll the device for any I/O. Polling the screen output simply pings
 * the device. If the device has closed for any reason, this operation
 * will return zero, and clean-up should be done.
 */
int hid_poll(hid_t *hid, struct hid_io *io, int mask);

/* Set which channels are enabled or disabled. Any bit found in `mask'
 * enables the corresponding channel. Bits that are not present have their
 * channels disabled.
 */
int hid_mask(hid_t *hid, int mask);

#endif /* TDA_HID_H */
