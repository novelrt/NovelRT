// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#ifndef NOVELRT_GRAPHICS_CAMERAFRAMESTATE_H

namespace NovelRT::Graphics {
  enum class CameraFrameState {
    Unmodified = 0,
    ModifiedInCurrent,
    ModifiedInLast
  };
}

#endif // !NOVELRT_GRAPHICS_CAMERAFRAMESTATE_H


