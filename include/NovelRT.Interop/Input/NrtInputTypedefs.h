// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INPUT_INPUTTYPEDEFS_H
#define NOVELRT_INTEROP_INPUT_INPUTTYPEDEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct NrtBasicInteractionRect* NrtBasicInteractionRectHandle;
    typedef struct NrtKeyStateFrameChangeLog* NrtKeyStateFrameChangeLogHandle;
    typedef struct NrtInteractionService* NrtInteractionServiceHandle;

    typedef enum
    {
        NRT_KEYCODE_NOTHING = -1,
        NRT_KEYCODE_ENTER = 257,
        NRT_KEYCODE_ESCAPE_KEY = 256,
        NRT_KEYCODE_BACKSPACE = 259,
        NRT_KEYCODE_TAB = 258,
        NRT_KEYCODE_SPACEBAR = 32,
        NRT_KEYCODE_SINGLE_QUOTE = 39,
        NRT_KEYCODE_LEFT_BRACKET = 91,
        NRT_KEYCODE_RIGHT_BRACKET = 93,
        NRT_KEYCODE_COMMA = 44,
        NRT_KEYCODE_MINUS = 45,
        NRT_KEYCODE_FULL_STOP = 46,
        NRT_KEYCODE_FORWARD_SLASH = 47,

        NRT_KEYCODE_ZERO = 48,
        NRT_KEYCODE_ONE = 49,
        NRT_KEYCODE_TWO = 50,
        NRT_KEYCODE_THREE = 51,
        NRT_KEYCODE_FOUR = 52,
        NRT_KEYCODE_FIVE = 53,
        NRT_KEYCODE_SIX = 54,
        NRT_KEYCODE_SEVEN = 55,
        NRT_KEYCODE_Eight = 56,
        NRT_KEYCODE_Nine = 57,

        NRT_KEYCODE_SEMICOLON = 59,
        NRT_KEYCODE_LEFT_SQUARE_BRACKET = 91,
        NRT_KEYCODE_BACK_SLASH = 92,
        NRT_KEYCODE_RIGHT_SQUARE_BRACKET = 93,
        NRT_KEYCODE_CARET = 96,

        NRT_KEYCODE_A = 65,
        NRT_KEYCODE_B = 66,
        NRT_KEYCODE_C = 67,
        NRT_KEYCODE_D = 68,
        NRT_KEYCODE_E = 69,
        NRT_KEYCODE_F = 70,
        NRT_KEYCODE_G = 71,
        NRT_KEYCODE_H = 72,
        NRT_KEYCODE_I = 73,
        NRT_KEYCODE_J = 74,
        NRT_KEYCODE_K = 75,
        NRT_KEYCODE_L = 76,
        NRT_KEYCODE_M = 77,
        NRT_KEYCODE_N = 78,
        NRT_KEYCODE_O = 79,
        NRT_KEYCODE_P = 80,
        NRT_KEYCODE_Q = 81,
        NRT_KEYCODE_R = 82,
        NRT_KEYCODE_S = 83,
        NRT_KEYCODE_T = 84,
        NRT_KEYCODE_U = 85,
        NRT_KEYCODE_V = 86,
        NRT_KEYCODE_W = 87,
        NRT_KEYCODE_X = 88,
        NRT_KEYCODE_Y = 89,
        NRT_KEYCODE_Z = 90,

        NRT_KEYCODE_CAPS_LOCK = 280,

        NRT_KEYCODE_F1 = 290,
        NRT_KEYCODE_F2 = 291,
        NRT_KEYCODE_F3 = 292,
        NRT_KEYCODE_F4 = 293,
        NRT_KEYCODE_F5 = 294,
        NRT_KEYCODE_F6 = 295,
        NRT_KEYCODE_F7 = 296,
        NRT_KEYCODE_F8 = 297,
        NRT_KEYCODE_F9 = 298,
        NRT_KEYCODE_F10 = 299,
        NRT_KEYCODE_F11 = 300,
        NRT_KEYCODE_F12 = 301,
        NRT_KEYCODE_F13 = 302,
        NRT_KEYCODE_F14 = 303,
        NRT_KEYCODE_F15 = 304,
        NRT_KEYCODE_F16 = 305,
        NRT_KEYCODE_F17 = 306,
        NRT_KEYCODE_F18 = 307,
        NRT_KEYCODE_F19 = 308,
        NRT_KEYCODE_F20 = 309,
        NRT_KEYCODE_F21 = 310,
        NRT_KEYCODE_F22 = 311,
        NRT_KEYCODE_F23 = 312,
        NRT_KEYCODE_F24 = 313,

        NRT_KEYCODE_PRINT_SCREEN = 283,
        NRT_KEYCODE_SCROLL_LOCK = 281,
        NRT_KEYCODE_PAUSE_BREAK = 284,
        NRT_KEYCODE_INSERT = 260,
        NRT_KEYCODE_HOME = 268,
        NRT_KEYCODE_PAGE_UP = 266,
        NRT_KEYCODE_DELETE = 261,
        NRT_KEYCODE_END = 269,
        NRT_KEYCODE_PAGE_DOWN = 267,

        NRT_KEYCODE_RIGHT_ARROW = 262,
        NRT_KEYCODE_LEFT_ARROW = 263,
        NRT_KEYCODE_DOWN_ARROW = 264,
        NRT_KEYCODE_UP_ARROW = 265,

        NRT_KEYCODE_NUM_LOCK = 282,
        NRT_KEYCODE_NUM_PAD_DIVIDE = 331,
        NRT_KEYCODE_NUM_PAD_MULTIPLY = 332,
        NRT_KEYCODE_NUM_PAD_MINUS = 333,
        NRT_KEYCODE_NUM_PAD_PLUS = 334,
        NRT_KEYCODE_NUM_PAD_ENTER = 335,
        NRT_KEYCODE_NUM_PAD_ONE = 321,
        NRT_KEYCODE_NUM_PAD_TWO = 322,
        NRT_KEYCODE_NUM_PAD_THREE = 323,
        NRT_KEYCODE_NUM_PAD_FOUR = 324,
        NRT_KEYCODE_NUM_PAD_FIVE = 325,
        NRT_KEYCODE_NUM_PAD_SIX = 326,
        NRT_KEYCODE_NUM_PAD_SEVEN = 327,
        NRT_KEYCODE_NUM_PAD_EIGHT = 328,
        NRT_KEYCODE_NUM_PAD_NINE = 329,
        NRT_KEYCODE_NUM_PAD_ZERO = 320,
        NRT_KEYCODE_NUM_PAD_FULL_STOP = 330,
        NRT_KEYCODE_NUM_PAD_EQUALS = 336,

        NRT_KEYCODE_MENU_KEY = 348,

        NRT_KEYCODE_LEFT_MOUSE_BUTTON = 0,
        NRT_KEYCODE_RIGHT_MOUSE_BUTTON = 1,
        NRT_KEYCODE_MIDDLE_MOUSE_BUTTON = 2,
        NRT_KEYCODE_MOUSE_BUTTON_FOUR = 3,
        NRT_KEYCODE_MOUSE_BUTTON_FIVE = 4,
        NRT_KEYCODE_MOUSE_BUTTON_SIX = 5,
        NRT_KEYCODE_MOUSE_BUTTON_SEVEN = 6,
        NRT_KEYCODE_MOUSE_BUTTON_EIGHT = 7,
        NRT_KEYCODE_FIRST_MOUSE_BUTTON = NRT_KEYCODE_LEFT_MOUSE_BUTTON,
        NRT_KEYCODE_LAST_MOUSE_BUTTON = NRT_KEYCODE_MOUSE_BUTTON_EIGHT
    } NrtKeyCodeKind;

    typedef enum
    {
        NRT_IDLE = -1,
        NRT_KEYUP = 0,
        NRT_KEYDOWN = 1,
        NRT_KEYDOWNHELD = 2,
    } NrtKeyStateKind;

    typedef int32_t NrtKeyCode;
    typedef int32_t NrtKeyState;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_INPUTTYPEDEFS_H
