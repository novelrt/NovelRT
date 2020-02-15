#ifndef NOVELRT_ANIMATION_SPRITEANIMATOR_H
#define NOVELRT_ANIMATION_SPRITEANIMATOR_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation {

  struct SpriteAnimatorState {
  public:
    std::vector<SpriteAnimatorFrame> frames;
    std::map<SpriteAnimatorState, std::vector, std::function<bool()>> transitions;
  };

  struct SpriteAnimatorFrame {
  public:
    Graphics::Texture texture;
    std::function<void()> onFrameEnter;
    std::function<void()> onFrameExit;
  };

  class SpriteAnimator {
  private:
    NovelRunner* _runner;
    std::vector<SpriteAnimatorState> _states;

  public:
    explicit SpriteAnimator(NovelRunner* runner) noexcept;
    void play();
    void pause();
    void stop();
  };
}

#endif