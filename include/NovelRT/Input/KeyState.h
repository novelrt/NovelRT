// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_KEYSTATE_H
#define NOVELRT_INPUT_KEYSTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input {
  /**
   * A set of key states.
   */
  enum class KeyState : int32_t {
    Idle = 0,
    KeyDown = GLFW_PRESS,
    KeyDownHeld = GLFW_REPEAT,
    KeyUp = GLFW_RELEASE,
  };
}

#endif // !NOVELRT_INPUT_KEYSTATE_H


