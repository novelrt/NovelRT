// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_INTEROP_INPUT_KEYCODE_H
#define NOVELRT_INTEROP_INPUT_KEYCODE_H

#ifdef __cplusplus
extern "C" {
#endif

//Mapped to GLFW for now
typedef enum {
    Nothing = -1,
    Enter = 257,
    EscapeKey = 256,
    Backspace = 259,
    Tab = 258,
    Spacebar = 32,
    SingleQuote = 39,
    LeftBracket = 91,
    RightBracket = 93,
    Comma = 44,
    Minus = 45,
    FullStop = 46,
    ForwardSlash = 47,

    Zero = 48,
    One = 49,
    Two = 50,
    Three = 51,
    Four = 52,
    Five = 53,
    Six = 54,
    Seven = 55,
    Eight = 56,
    Nine = 57,

    Semicolon = 59,
    LeftSquareBracket = 91,
    BackSlash = 92,
    RightSquareBracket = 93,
    Caret = 96,

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    CapsLock = 280,

    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,


    PrintScreen = 283,
    ScrollLock = 281,
    PauseBreak = 284,
    Insert = 260,
    Home = 268,
    PageUp = 266,
    Delete = 261,
    End = 269,
    PageDown = 267,

    RightArrow = 262,
    LeftArrow = 263,
    DownArrow = 264,
    UpArrow = 265,

    NumLock = 282,
    NumPadDivide = 331,
    NumPadMultiply = 332,
    NumPadMinus = 333,
    NumPadPlus = 334,
    NumPadEnter = 335,
    NumPadOne = 321,
    NumPadTwo = 322,
    NumPadThree = 323,
    NumPadFour = 324,
    NumPadFive = 325,
    NumPadSix = 326,
    NumPadSeven = 327,
    NumPadEight = 328,
    NumPadNine = 329,
    NumPadZero = 320,
    NumPadFullStop = 330,
    NumPadEquals = 336,

    MenuKey = 348,

    //The next members should only be used when checking MouseEvents

    LeftMouseButton = 0,
    RightMouseButton = 1,
    MiddleMouseButton = 2,
    MouseButtonFour = 3,
    MouseButtonFive = 4,
    MouseButtonSix = 5,
    MouseButtonSeven = 6,
    MouseButtonEight = 7,
    FirstMouseButton = LeftMouseButton,
    LastMouseButton = MouseButtonEight
}  NovelRTKeyCode;

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INPUT_KEYCODE_H