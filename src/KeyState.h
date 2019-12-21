#ifndef NOVELRT_KEYSTATE_H
#include <stdint.h>

namespace NovelRT {
  enum class KeyState : uint32_t {
    Idle = 0,
    KeyDown = 1,
    KeyDownHeld = 2,
    KeyUp = 3,
  };
}
#endif // !NOVELRT_KEYSTATE_H


