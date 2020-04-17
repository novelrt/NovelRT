// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INPUT_KEYSTATEFRAMEUPDATEPAIR_H
#define NOVELRT_INPUT_KEYSTATEFRAMEUPDATEPAIR_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Input {
  struct KeyStateFrameUpdatePair {
    KeyState currentState;
    bool wasUpdatedThisFrame;
  };
}

#endif //!NOVELRT_INPUT_KEYSTATEFRAMEUPDATEPAIR_H
