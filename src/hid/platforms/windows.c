#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <tda/mm.h>
#include <tda/hid.h>
#include <tda/hid/keyboard.h>

#include <hid/platforms/windows/keyboard.h>

struct hid
{
	HWND     wnd;
	HDC      dc;
	HGLRC    glrc;
	int      mask; /* Which channels are enabled */
	short    mouse_x;
	short    mouse_y;
	short    mouse_last_x;
	short    mouse_last_y;
};

static LRESULT CALLBACK window_proc(
	HWND wnd,
	UINT msg,
	WPARAM w,
	LPARAM l
	)
{
	hid_t *hid;

	hid = (hid_t *)GetWindowLongPtr(wnd, GWLP_USERDATA);

	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(wnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		hid->mouse_x = GET_X_LPARAM(l);
		hid->mouse_y = GET_Y_LPARAM(l);
		break;
	default:
		return DefWindowProc(wnd, msg, w, l);
	}

	return 0;
}

static int create_window_class(void);
static void init_keyboard_key_mapping(void);
static void destroy_window_class(void);
static int create_window(hid_t *hid, const struct hid_format *fmt);
static int create_context(hid_t *hid, const struct hid_format *fmt);
static int set_pixel_format(HDC dc, const struct hid_format *fmt);
static int keyboard_io_poll(hid_t *hid, struct hid_io *io, const MSG *msg);
static int mouse_io_poll(hid_t *hid, struct hid_io *io, const MSG *msg);
static int mouse_move_io_poll(hid_t *hid, struct hid_io *io);

static ATOM window_class;

static int keymap[0xFF];

static int is_init;

static const struct hid_format default_format = {
	.default_width = 800,
	.default_height = 600,
	.red_bits = 8,
	.blue_bits = 8,
	.green_bits = 8,
	.alpha_bits = 8,
	.depth_bits = 24,
	.stencil_bits = 8
	};

int hid_init(int argc, const char *argv[])
{
	if (!create_window_class())
		return 0;

	is_init = 1;

	return 1;
}

void hid_deinit(void)
{
	destroy_window_class();

	is_init = 0;
}

int hid_is_init(void)
{
	return is_init;
}

hid_t *hid_create(const struct hid_format *fmt)
{
	hid_t *hid;

	hid = pool_malloc(sizeof(*hid));
	if (!hid)
		return 0;

	if (!fmt)
		fmt = &default_format;

	if (!create_window(hid, fmt))
		goto err;

	if (!create_context(hid, fmt))
		goto err;

	SetWindowLongPtr(hid->wnd, GWLP_USERDATA, (LONG)hid);

	hid_mask(hid, HID_ALL_CHANNELS);

	hid->mouse_x = 0;
	hid->mouse_y = 0;
	hid->mouse_last_x = 0;
	hid->mouse_last_y = 0;

	return hid;
err:
	hid_destroy(hid);

	return 0;
}

void hid_destroy(hid_t *hid)
{
	if (!hid)
		return;

	pool_free(hid);
}

int hid_clear(hid_t *hid, int mask)
{
	if (!hid)
		return 0;

	if (mask & HID_CHANNEL_SCREEN) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	return 1;
}

int hid_flush(hid_t *hid, int mask)
{
	if (!hid)
		return 0;

	if (mask & HID_CHANNEL_SCREEN)
		SwapBuffers(hid->dc);

	return 1;
}

int hid_poll(hid_t *hid, struct hid_io *io, int mask)
{
	MSG msg;
	int tmp = 0;

	if (!hid)
		return 0;

	if (!mask)
		return IsWindow(hid->wnd) == TRUE ? 1 : 0;

	if (hid->mouse_last_x != hid->mouse_x || hid->mouse_last_y != hid->mouse_y)
		return mouse_move_io_poll(hid, io);

	if (!PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		return 0;

	if (!io)
		goto out;

	switch (msg.message) {
	case WM_KEYDOWN:
	case WM_KEYUP:
		tmp = keyboard_io_poll(hid, io, &msg);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		tmp = mouse_io_poll(hid, io, &msg);
		break;
	default:
		io->type = 0;
	}
out:
	TranslateMessage(&msg);
	DispatchMessage(&msg);

	return tmp;
}

int create_window_class(void)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = window_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "TDA_WND_CLASS";
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

	window_class = RegisterClassEx(&wc);

	if (!window_class)
		return 0;

	init_keyboard_key_mapping();

	atexit(destroy_window_class);

	return 1;
}

void init_keyboard_key_mapping(void)
{
	keymap[WINDOWS_KEYBOARD_SPACE] = KEYBOARD_SPACE;
	keymap[WINDOWS_KEYBOARD_APOSTROPHE] = KEYBOARD_APOSTROPHE;
	keymap[WINDOWS_KEYBOARD_COMMA] = KEYBOARD_COMMA;
	keymap[WINDOWS_KEYBOARD_MINUS] = KEYBOARD_MINUS;
	keymap[WINDOWS_KEYBOARD_PERIOD] = KEYBOARD_PERIOD;
	keymap[WINDOWS_KEYBOARD_SLASH] = KEYBOARD_SLASH;
	keymap[WINDOWS_KEYBOARD_0] = KEYBOARD_0;
	keymap[WINDOWS_KEYBOARD_1] = KEYBOARD_1;
	keymap[WINDOWS_KEYBOARD_2] = KEYBOARD_2;
	keymap[WINDOWS_KEYBOARD_3] = KEYBOARD_3;
	keymap[WINDOWS_KEYBOARD_4] = KEYBOARD_4;
	keymap[WINDOWS_KEYBOARD_5] = KEYBOARD_5;
	keymap[WINDOWS_KEYBOARD_6] = KEYBOARD_6;
	keymap[WINDOWS_KEYBOARD_7] = KEYBOARD_7;
	keymap[WINDOWS_KEYBOARD_8] = KEYBOARD_8;
	keymap[WINDOWS_KEYBOARD_9] = KEYBOARD_9;
	keymap[WINDOWS_KEYBOARD_SEMICOLON] = KEYBOARD_SEMICOLON;
	keymap[WINDOWS_KEYBOARD_EQUAL] = KEYBOARD_EQUAL;
	keymap[WINDOWS_KEYBOARD_A] = KEYBOARD_A;
	keymap[WINDOWS_KEYBOARD_B] = KEYBOARD_B;
	keymap[WINDOWS_KEYBOARD_C] = KEYBOARD_C;
	keymap[WINDOWS_KEYBOARD_D] = KEYBOARD_D;
	keymap[WINDOWS_KEYBOARD_E] = KEYBOARD_E;
	keymap[WINDOWS_KEYBOARD_F] = KEYBOARD_F;
	keymap[WINDOWS_KEYBOARD_G] = KEYBOARD_G;
	keymap[WINDOWS_KEYBOARD_H] = KEYBOARD_H;
	keymap[WINDOWS_KEYBOARD_I] = KEYBOARD_I;
	keymap[WINDOWS_KEYBOARD_J] = KEYBOARD_J;
	keymap[WINDOWS_KEYBOARD_K] = KEYBOARD_K;
	keymap[WINDOWS_KEYBOARD_L] = KEYBOARD_L;
	keymap[WINDOWS_KEYBOARD_M] = KEYBOARD_M;
	keymap[WINDOWS_KEYBOARD_N] = KEYBOARD_N;
	keymap[WINDOWS_KEYBOARD_O] = KEYBOARD_O;
	keymap[WINDOWS_KEYBOARD_P] = KEYBOARD_P;
	keymap[WINDOWS_KEYBOARD_Q] = KEYBOARD_Q;
	keymap[WINDOWS_KEYBOARD_R] = KEYBOARD_R;
	keymap[WINDOWS_KEYBOARD_S] = KEYBOARD_S;
	keymap[WINDOWS_KEYBOARD_T] = KEYBOARD_T;
	keymap[WINDOWS_KEYBOARD_U] = KEYBOARD_U;
	keymap[WINDOWS_KEYBOARD_V] = KEYBOARD_V;
	keymap[WINDOWS_KEYBOARD_W] = KEYBOARD_W;
	keymap[WINDOWS_KEYBOARD_X] = KEYBOARD_X;
	keymap[WINDOWS_KEYBOARD_Y] = KEYBOARD_Y;
	keymap[WINDOWS_KEYBOARD_Z] = KEYBOARD_Z;
	keymap[WINDOWS_KEYBOARD_LEFT_BRACKET] = KEYBOARD_LEFT_BRACKET;
	keymap[WINDOWS_KEYBOARD_BACKSLASH] = KEYBOARD_BACKSLASH;
	keymap[WINDOWS_KEYBOARD_RIGHT_BRACKET] = KEYBOARD_RIGHT_BRACKET;
	keymap[WINDOWS_KEYBOARD_GRAVE_ACCENT] = KEYBOARD_GRAVE_ACCENT;
	keymap[WINDOWS_KEYBOARD_ESCAPE] = KEYBOARD_ESCAPE;
	keymap[WINDOWS_KEYBOARD_ENTER] = KEYBOARD_ENTER;
	keymap[WINDOWS_KEYBOARD_TAB] = KEYBOARD_TAB;
	keymap[WINDOWS_KEYBOARD_BACKSPACE] = KEYBOARD_BACKSPACE;
	keymap[WINDOWS_KEYBOARD_INSERT] = KEYBOARD_INSERT;
	keymap[WINDOWS_KEYBOARD_DELETE] = KEYBOARD_DELETE;
	keymap[WINDOWS_KEYBOARD_RIGHT] = KEYBOARD_RIGHT;
	keymap[WINDOWS_KEYBOARD_LEFT] = KEYBOARD_LEFT;
	keymap[WINDOWS_KEYBOARD_DOWN] = KEYBOARD_DOWN;
	keymap[WINDOWS_KEYBOARD_UP] = KEYBOARD_UP;
	keymap[WINDOWS_KEYBOARD_PAGE_UP] = KEYBOARD_PAGE_UP;
	keymap[WINDOWS_KEYBOARD_PAGE_DOWN] = KEYBOARD_PAGE_DOWN;
	keymap[WINDOWS_KEYBOARD_HOME] = KEYBOARD_HOME;
	keymap[WINDOWS_KEYBOARD_END] = KEYBOARD_END;
	keymap[WINDOWS_KEYBOARD_CAPS_LOCK] = KEYBOARD_CAPS_LOCK;
	keymap[WINDOWS_KEYBOARD_SCROLL_LOCK] = KEYBOARD_SCROLL_LOCK;
	keymap[WINDOWS_KEYBOARD_NUM_LOCK] = KEYBOARD_NUM_LOCK;
	keymap[WINDOWS_KEYBOARD_PRINT_SCREEN] = KEYBOARD_PRINT_SCREEN;
	keymap[WINDOWS_KEYBOARD_PAUSE] = KEYBOARD_PAUSE;
	keymap[WINDOWS_KEYBOARD_F1] = KEYBOARD_F1;
	keymap[WINDOWS_KEYBOARD_F2] = KEYBOARD_F2;
	keymap[WINDOWS_KEYBOARD_F3] = KEYBOARD_F3;
	keymap[WINDOWS_KEYBOARD_F4] = KEYBOARD_F4;
	keymap[WINDOWS_KEYBOARD_F5] = KEYBOARD_F5;
	keymap[WINDOWS_KEYBOARD_F6] = KEYBOARD_F6;
	keymap[WINDOWS_KEYBOARD_F7] = KEYBOARD_F7;
	keymap[WINDOWS_KEYBOARD_F8] = KEYBOARD_F8;
	keymap[WINDOWS_KEYBOARD_F9] = KEYBOARD_F9;
	keymap[WINDOWS_KEYBOARD_F10] = KEYBOARD_F10;
	keymap[WINDOWS_KEYBOARD_F11] = KEYBOARD_F11;
	keymap[WINDOWS_KEYBOARD_F12] = KEYBOARD_F12;
	keymap[WINDOWS_KEYBOARD_KP_0] = KEYBOARD_KP_0;
	keymap[WINDOWS_KEYBOARD_KP_1] = KEYBOARD_KP_1;
	keymap[WINDOWS_KEYBOARD_KP_2] = KEYBOARD_KP_2;
	keymap[WINDOWS_KEYBOARD_KP_3] = KEYBOARD_KP_3;
	keymap[WINDOWS_KEYBOARD_KP_4] = KEYBOARD_KP_4;
	keymap[WINDOWS_KEYBOARD_KP_5] = KEYBOARD_KP_5;
	keymap[WINDOWS_KEYBOARD_KP_6] = KEYBOARD_KP_6;
	keymap[WINDOWS_KEYBOARD_KP_7] = KEYBOARD_KP_7;
	keymap[WINDOWS_KEYBOARD_KP_8] = KEYBOARD_KP_8;
	keymap[WINDOWS_KEYBOARD_KP_9] = KEYBOARD_KP_9;
	keymap[WINDOWS_KEYBOARD_KP_DECIMAL] = KEYBOARD_KP_DECIMAL;
	keymap[WINDOWS_KEYBOARD_KP_DIVIDE] = KEYBOARD_KP_DIVIDE;
	keymap[WINDOWS_KEYBOARD_KP_MULTIPLY] = KEYBOARD_KP_MULTIPLY;
	keymap[WINDOWS_KEYBOARD_KP_SUBTRACT] = KEYBOARD_KP_SUBTRACT;
	keymap[WINDOWS_KEYBOARD_KP_ADD] = KEYBOARD_KP_ADD;
	keymap[WINDOWS_KEYBOARD_KP_ENTER] = KEYBOARD_KP_ENTER;
	keymap[WINDOWS_KEYBOARD_LEFT_SHIFT] = KEYBOARD_LEFT_SHIFT;
	keymap[WINDOWS_KEYBOARD_LEFT_CONTROL] = KEYBOARD_LEFT_CONTROL;
	keymap[WINDOWS_KEYBOARD_LEFT_ALT] = KEYBOARD_LEFT_ALT;
	keymap[WINDOWS_KEYBOARD_LEFT_SUPER] = KEYBOARD_LEFT_SUPER;
	keymap[WINDOWS_KEYBOARD_RIGHT_SHIFT] = KEYBOARD_RIGHT_SHIFT;
	keymap[WINDOWS_KEYBOARD_RIGHT_CONTROL] = KEYBOARD_RIGHT_CONTROL;
	keymap[WINDOWS_KEYBOARD_RIGHT_ALT] = KEYBOARD_RIGHT_ALT;
	keymap[WINDOWS_KEYBOARD_RIGHT_SUPER] = KEYBOARD_RIGHT_SUPER;
	keymap[WINDOWS_KEYBOARD_MENU] = KEYBOARD_MENU;
}

int hid_mask(hid_t *hid, int mask)
{
	if (mask & HID_CHANNEL_SCREEN)
		ShowWindow(hid->wnd, SW_SHOWDEFAULT);
	else
		ShowWindow(hid->wnd, SW_HIDE);

	hid->mask = mask;

	return 1;
}

void destroy_window_class(void)
{
	UnregisterClass(MAKEINTATOM(window_class), GetModuleHandle(0));
}

int create_window(hid_t *hid, const struct hid_format *fmt)
{
	HWND wnd;

	if (!is_init)
		return 0;

	wnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		MAKEINTATOM(window_class),
		"Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		fmt->default_width,
		fmt->default_height,
		0,
		0,
		GetModuleHandle(0),
		0
		);

	if (!wnd)
		return 0;

	hid->wnd = wnd;

	return 1;
}

int create_context(hid_t *hid, const struct hid_format *fmt)
{
	HDC dc;
	HGLRC glrc;

	dc = GetDC(hid->wnd);
	if (!dc)
		return 0;

	if (!set_pixel_format(dc, fmt))
		return 0;

	glrc = wglCreateContext(dc);
	if (!glrc)
		return 0;

	hid->dc = dc;
	hid->glrc = glrc;

	wglMakeCurrent(dc, glrc);

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

	return 1;
}


int set_pixel_format(HDC dc, const struct hid_format *fmt)
{
	PIXELFORMATDESCRIPTOR desc;
	int format;

	desc.nSize          = sizeof(desc);
	desc.nVersion       = 1;
	desc.iPixelType     = PFD_TYPE_RGBA;
	desc.cRedBits       = fmt->red_bits;
	desc.cBlueBits      = fmt->blue_bits;
	desc.cGreenBits     = fmt->green_bits;
	desc.cAlphaBits     = fmt->alpha_bits;
	desc.cDepthBits     = fmt->depth_bits;
	desc.cStencilBits   = fmt->stencil_bits;
	desc.iLayerType     = PFD_MAIN_PLANE;

	desc.dwFlags        = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
	                      | PFD_DOUBLEBUFFER;

	desc.cColorBits     = fmt->red_bits + fmt->green_bits
	                       + fmt->blue_bits + fmt->alpha_bits;

	format = ChoosePixelFormat(dc, &desc);

	if (!format)
		return 0;

	if (SetPixelFormat(dc, format, &desc))
		return 1;
	else
		return 0;
}

int keyboard_io_poll(hid_t *hid, struct hid_io *io, const MSG *msg)
{
	char keyboard_state[256];
	int tmp;
	WORD c;

	if (!(hid->mask & HID_CHANNEL_KEYBOARD))
		return 0;

	if (!GetKeyboardState(keyboard_state))
		return 0;

	tmp = ToAscii(
		msg->wParam,
		MapVirtualKey(msg->wParam, MAPVK_VK_TO_VSC) | 0x80000000,
		keyboard_state,
		&c,
		0
		);

	switch (tmp) {
	case 1:
		io->keyboard.key = c;
		break;
	case 0:
	case 2:
	default:
		io->keyboard.key = 0;
	}

	io->type = HID_IO_KEYBOARD;
	io->keyboard.scan_code = keymap[msg->wParam];
	io->keyboard.pressed = msg->message == WM_KEYDOWN ? 1 : 0;

	return 1;
}

int mouse_io_poll(hid_t *hid, struct hid_io *io, const MSG *msg)
{
	if (!(hid->mask & HID_CHANNEL_MOUSE))
		return 0;

	io->type = HID_IO_MOUSE;

	io->mouse.subtype = HID_MOUSE_IO_BUTTON;

	switch (msg->message) {
	case WM_LBUTTONDOWN:
		io->mouse.button = 1;
		io->mouse.pressed = 1;
		break;
	case WM_RBUTTONDOWN:
		io->mouse.button = 2;
		io->mouse.pressed = 1;
		break;
	case WM_LBUTTONUP:
		io->mouse.button = 1;
		io->mouse.pressed = 0;
		break;
	case WM_RBUTTONUP:
		io->mouse.button = 2;
		io->mouse.pressed = 0;
		break;
	default:
		return 0;
	}

	return 1;
}

int mouse_move_io_poll(hid_t *hid, struct hid_io *io)
{
	if (!(hid->mask & HID_CHANNEL_MOUSE))
		return 0;

	io->type = HID_IO_MOUSE;

	io->mouse.subtype = HID_MOUSE_IO_MOTION;

	io->mouse.x = hid->mouse_x;
	io->mouse.y = hid->mouse_y;
	io->mouse.dx = hid->mouse_x - hid->mouse_last_x;
	io->mouse.dy = hid->mouse_y - hid->mouse_last_y;
	hid->mouse_last_x = hid->mouse_x;
	hid->mouse_last_y = hid->mouse_y;

	return 1;
}
