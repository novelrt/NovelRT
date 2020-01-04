// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_GRAPHICS_CAMERAFRAMESTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics {
  enum class CameraFrameState {
    Unmodified,
    ModifiedInCurrent,
    ModifiedInLast
  };
}

#endif // !NOVELRT_GRAPHICS_CAMERAFRAMESTATE_H


