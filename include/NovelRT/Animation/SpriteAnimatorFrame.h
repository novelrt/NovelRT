// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation {
  class SpriteAnimatorFrame {
  public:
    Utilities::Event<> FrameEnter;
    Utilities::Event<> FrameExit;

  private:
    std::shared_ptr<Graphics::Texture> _texture;
    float _duration;

  public:

    inline std::shared_ptr<Graphics::Texture> getTexture() const noexcept {
      return _texture;
    }

    inline void setTexture(std::shared_ptr<Graphics::Texture> value) noexcept {
      _texture = value;
    }

    inline float getDuration() const noexcept {
      return _duration;
    }

    inline void setDuration(float value) noexcept {
      _duration = value;
    }
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H
