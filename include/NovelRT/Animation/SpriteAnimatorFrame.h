// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H
#define NOVELRT_ANIMATION_SPRITEANIMATORFRAME_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation {
  class SpriteAnimatorFrame {
  private:
    std::shared_ptr<Graphics::Texture> _texture;
    std::function<void()> _onFrameEnter;
    std::function<void()> _onFrameExit;
    float _duration;

  public:
    inline std::shared_ptr<Graphics::Texture> getTexture() const noexcept {
      return _texture;
    }

    inline void setTexture(std::shared_ptr<Graphics::Texture> value) noexcept {
      _texture = value;
    }

    inline std::function<void()> getOnFrameEnterDelegate() const noexcept {
      return _onFrameEnter;
    }

    inline void setOnFrameEnterDelegate(const std::function<void()>& value) {
      _onFrameEnter = value;
    }

    inline std::function<void()> getOnFrameExitDelegate() const noexcept {
      return _onFrameExit;
    }

    inline void setOnFrameExitDelegate(const std::function<void()>& value) noexcept {
      _onFrameExit = value;
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
