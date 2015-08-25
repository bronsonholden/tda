#ifndef __HID_PLATFORMS_WINDOWS_KEYBOARD_H
#define __HID_PLATFORMS_WINDOWS_KEYBOARD_H

#ifdef _MSC_VER

#include <windows.h>
#include <winuser.h>

#define WINDOWS_KEYBOARD_SPACE                0x20
#define WINDOWS_KEYBOARD_APOSTROPHE           0xDE
#define WINDOWS_KEYBOARD_COMMA                0xBC
#define WINDOWS_KEYBOARD_MINUS                0xBD
#define WINDOWS_KEYBOARD_PERIOD               0xBE
#define WINDOWS_KEYBOARD_SLASH                0xBF
#define WINDOWS_KEYBOARD_0                    0x30
#define WINDOWS_KEYBOARD_1                    0x31
#define WINDOWS_KEYBOARD_2                    0x32
#define WINDOWS_KEYBOARD_3                    0x33
#define WINDOWS_KEYBOARD_4                    0x34
#define WINDOWS_KEYBOARD_5                    0x35
#define WINDOWS_KEYBOARD_6                    0x36
#define WINDOWS_KEYBOARD_7                    0x37
#define WINDOWS_KEYBOARD_8                    0x38
#define WINDOWS_KEYBOARD_9                    0x39
#define WINDOWS_KEYBOARD_SEMICOLON            0xBA
#define WINDOWS_KEYBOARD_EQUAL                0xBB
#define WINDOWS_KEYBOARD_A                    0x41
#define WINDOWS_KEYBOARD_B                    0x42
#define WINDOWS_KEYBOARD_C                    0x43
#define WINDOWS_KEYBOARD_D                    0x44
#define WINDOWS_KEYBOARD_E                    0x45
#define WINDOWS_KEYBOARD_F                    0x46
#define WINDOWS_KEYBOARD_G                    0x47
#define WINDOWS_KEYBOARD_H                    0x48
#define WINDOWS_KEYBOARD_I                    0x49
#define WINDOWS_KEYBOARD_J                    0x4A
#define WINDOWS_KEYBOARD_K                    0x4B
#define WINDOWS_KEYBOARD_L                    0x4C
#define WINDOWS_KEYBOARD_M                    0x4D
#define WINDOWS_KEYBOARD_N                    0x4E
#define WINDOWS_KEYBOARD_O                    0x4F
#define WINDOWS_KEYBOARD_P                    0x50
#define WINDOWS_KEYBOARD_Q                    0x51
#define WINDOWS_KEYBOARD_R                    0x52
#define WINDOWS_KEYBOARD_S                    0x53
#define WINDOWS_KEYBOARD_T                    0x54
#define WINDOWS_KEYBOARD_U                    0x55
#define WINDOWS_KEYBOARD_V                    0x56
#define WINDOWS_KEYBOARD_W                    0x57
#define WINDOWS_KEYBOARD_X                    0x58
#define WINDOWS_KEYBOARD_Y                    0x59
#define WINDOWS_KEYBOARD_Z                    0x5A
#define WINDOWS_KEYBOARD_LEFT_BRACKET         0xDB
#define WINDOWS_KEYBOARD_BACKSLASH            0xDC
#define WINDOWS_KEYBOARD_RIGHT_BRACKET        0xDD
#define WINDOWS_KEYBOARD_GRAVE_ACCENT         0xC0
#define WINDOWS_KEYBOARD_ESCAPE               0x1B
#define WINDOWS_KEYBOARD_ENTER                0x0D
#define WINDOWS_KEYBOARD_TAB                  0x09
#define WINDOWS_KEYBOARD_BACKSPACE            0x08
#define WINDOWS_KEYBOARD_INSERT               0x2D
#define WINDOWS_KEYBOARD_DELETE               0x2E
#define WINDOWS_KEYBOARD_RIGHT                0x27
#define WINDOWS_KEYBOARD_LEFT                 0x25
#define WINDOWS_KEYBOARD_DOWN                 0x28
#define WINDOWS_KEYBOARD_UP                   0x26
#define WINDOWS_KEYBOARD_PAGE_UP              0x21
#define WINDOWS_KEYBOARD_PAGE_DOWN            0x22
#define WINDOWS_KEYBOARD_HOME                 0x24
#define WINDOWS_KEYBOARD_END                  0x23
#define WINDOWS_KEYBOARD_CAPS_LOCK            0x14
#define WINDOWS_KEYBOARD_SCROLL_LOCK          0x91
#define WINDOWS_KEYBOARD_NUM_LOCK             0x90
#define WINDOWS_KEYBOARD_PRINT_SCREEN         0x2A
#define WINDOWS_KEYBOARD_PAUSE                0x13
#define WINDOWS_KEYBOARD_F1                   0x70
#define WINDOWS_KEYBOARD_F2                   0x71
#define WINDOWS_KEYBOARD_F3                   0x72
#define WINDOWS_KEYBOARD_F4                   0x73
#define WINDOWS_KEYBOARD_F5                   0x74
#define WINDOWS_KEYBOARD_F6                   0x75
#define WINDOWS_KEYBOARD_F7                   0x76
#define WINDOWS_KEYBOARD_F8                   0x77
#define WINDOWS_KEYBOARD_F9                   0x78
#define WINDOWS_KEYBOARD_F10                  0x79
#define WINDOWS_KEYBOARD_F11                  0x7A
#define WINDOWS_KEYBOARD_F12                  0x7B
#define WINDOWS_KEYBOARD_KP_0                 0x60
#define WINDOWS_KEYBOARD_KP_1                 0x61
#define WINDOWS_KEYBOARD_KP_2                 0x62
#define WINDOWS_KEYBOARD_KP_3                 0x63
#define WINDOWS_KEYBOARD_KP_4                 0x64
#define WINDOWS_KEYBOARD_KP_5                 0x65
#define WINDOWS_KEYBOARD_KP_6                 0x66
#define WINDOWS_KEYBOARD_KP_7                 0x67
#define WINDOWS_KEYBOARD_KP_8                 0x68
#define WINDOWS_KEYBOARD_KP_9                 0x69
#define WINDOWS_KEYBOARD_KP_DECIMAL           0x6E
#define WINDOWS_KEYBOARD_KP_DIVIDE            0x6F
#define WINDOWS_KEYBOARD_KP_MULTIPLY          0x6A
#define WINDOWS_KEYBOARD_KP_SUBTRACT          0x6D
#define WINDOWS_KEYBOARD_KP_ADD               0x6B
#define WINDOWS_KEYBOARD_KP_ENTER             0x0D
#define WINDOWS_KEYBOARD_LEFT_SHIFT           0xA0
#define WINDOWS_KEYBOARD_LEFT_CONTROL         0xA2
#define WINDOWS_KEYBOARD_LEFT_ALT             0xA4
#define WINDOWS_KEYBOARD_LEFT_SUPER           0x5B
#define WINDOWS_KEYBOARD_RIGHT_SHIFT          0xA1
#define WINDOWS_KEYBOARD_RIGHT_CONTROL        0xA3
#define WINDOWS_KEYBOARD_RIGHT_ALT            0xA5
#define WINDOWS_KEYBOARD_RIGHT_SUPER          0x5C
#define WINDOWS_KEYBOARD_MENU                 0x5D

#endif /* _MSC_VER */

#endif /* __HID_PLATFORMS_WINDOWS_KEYBOARD_H */