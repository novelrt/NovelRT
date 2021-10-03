// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INPUT_KEYCODE_H
#define NOVELRT_INPUT_KEYCODE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input
{
    /**
     * @brief A set of key codes.
     */
    enum class KeyCode : int32_t
    {
        Nothing = GLFW_KEY_UNKNOWN,
        Enter = GLFW_KEY_ENTER,
        Escape = GLFW_KEY_ESCAPE,
        Backspace = GLFW_KEY_BACKSPACE,
        Tab = GLFW_KEY_TAB,
        Spacebar = GLFW_KEY_SPACE,
        SingleQuote = GLFW_KEY_APOSTROPHE,
        LeftBracket = GLFW_KEY_LEFT_BRACKET,
        RightBracket = GLFW_KEY_RIGHT_BRACKET,
        Comma = GLFW_KEY_COMMA,
        Minus = GLFW_KEY_MINUS,
        FullStop = GLFW_KEY_PERIOD,
        ForwardSlash = GLFW_KEY_SLASH,

        Zero = GLFW_KEY_0,
        One = GLFW_KEY_1,
        Two = GLFW_KEY_2,
        Three = GLFW_KEY_3,
        Four = GLFW_KEY_4,
        Five = GLFW_KEY_5,
        Six = GLFW_KEY_6,
        Seven = GLFW_KEY_7,
        Eight = GLFW_KEY_8,
        Nine = GLFW_KEY_9,

        Semicolon = GLFW_KEY_SEMICOLON,
        LeftSquareBracket = GLFW_KEY_LEFT_BRACKET,
        BackSlash = GLFW_KEY_BACKSLASH,
        RightSquareBracket = GLFW_KEY_RIGHT_BRACKET,
        Caret = GLFW_KEY_GRAVE_ACCENT,

        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        CapsLock = GLFW_KEY_CAPS_LOCK,

        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,

        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        ScrollLock = GLFW_KEY_SCROLL_LOCK,
        PauseBreak = GLFW_KEY_PAUSE,
        Insert = GLFW_KEY_INSERT,
        Home = GLFW_KEY_HOME,
        PageUp = GLFW_KEY_PAGE_UP,
        Delete = GLFW_KEY_DELETE,
        End = GLFW_KEY_END,
        PageDown = GLFW_KEY_PAGE_DOWN,

        RightArrow = GLFW_KEY_RIGHT,
        LeftArrow = GLFW_KEY_LEFT,
        DownArrow = GLFW_KEY_DOWN,
        UpArrow = GLFW_KEY_UP,

        NumLock = GLFW_KEY_NUM_LOCK,
        NumPadDivide = GLFW_KEY_KP_DIVIDE,
        NumPadMultiply = GLFW_KEY_KP_MULTIPLY,
        NumPadMinus = GLFW_KEY_KP_SUBTRACT,
        NumPadPlus = GLFW_KEY_KP_ADD,
        NumPadEnter = GLFW_KEY_KP_ENTER,
        NumPadOne = GLFW_KEY_KP_1,
        NumPadTwo = GLFW_KEY_KP_2,
        NumPadThree = GLFW_KEY_KP_3,
        NumPadFour = GLFW_KEY_KP_4,
        NumPadFive = GLFW_KEY_KP_5,
        NumPadSix = GLFW_KEY_KP_6,
        NumPadSeven = GLFW_KEY_KP_7,
        NumPadEight = GLFW_KEY_KP_8,
        NumPadNine = GLFW_KEY_KP_9,
        NumPadZero = GLFW_KEY_KP_0,
        NumPadFullStop = GLFW_KEY_KP_DECIMAL,
        NumPadEquals = GLFW_KEY_KP_EQUAL,

        MenuKey = GLFW_KEY_MENU,

        // The next members should only be used when checking MouseEvents

        LeftMouseButton = GLFW_MOUSE_BUTTON_LEFT,
        RightMouseButton = GLFW_MOUSE_BUTTON_RIGHT,
        MiddleMouseButton = GLFW_MOUSE_BUTTON_MIDDLE,
        MouseButtonFour = GLFW_MOUSE_BUTTON_4,
        MouseButtonFive = GLFW_MOUSE_BUTTON_5,
        MouseButtonSix = GLFW_MOUSE_BUTTON_6,
        MouseButtonSeven = GLFW_MOUSE_BUTTON_7,
        MouseButtonEight = GLFW_MOUSE_BUTTON_8,
        FirstMouseButton = LeftMouseButton,
        LastMouseButton = GLFW_MOUSE_BUTTON_LAST
    };
}

#endif // NOVELRT_INPUT_KEYCODE_H
