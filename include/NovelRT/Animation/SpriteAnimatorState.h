// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation {
  class SpriteAnimatorState {
  private:
    std::vector<SpriteAnimatorFrame> _frames;
    bool _shouldLoop;
    std::vector<std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>> _transitions;

  public:

    inline void insertNewState(std::shared_ptr<SpriteAnimatorState> stateTarget, std::vector<std::function<bool()>> transitionConditions) {
      _transitions.emplace_back(make_tuple(stateTarget, transitionConditions));
    }

    inline void removeStateAtIndex(int32_t index) { //not sure if we can make this noexcept somehow but whatever
      _transitions.erase(_transitions.begin() + index);
    }

    inline bool getShouldLoop() const noexcept {
      return _shouldLoop;
    }

    inline void setShouldLoop(bool value) noexcept {
      _shouldLoop = value;
    }

    inline const std::vector<SpriteAnimatorFrame>* getFrames() const noexcept {
      return &_frames;
    }

    inline void setFrames(const std::vector<SpriteAnimatorFrame>& value) noexcept {
      _frames = value;
    }

    inline void setTransitions(const std::vector<std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>>& value) noexcept {
      _transitions = value;
    }

    inline std::shared_ptr<SpriteAnimatorState> tryFindValidTransition() {
      for (auto transitionTuple : _transitions) {
        auto conditions = std::get<std::vector<std::function<bool()>>>(transitionTuple);
        bool shouldTransitionToThisState = true;

        for (auto condition : conditions) {
          if (condition()) continue;

          shouldTransitionToThisState = false;
          break;
        }

        if (!shouldTransitionToThisState) continue;

        auto returnValue = std::get<std::shared_ptr<SpriteAnimatorState>>(transitionTuple);

        break;

      }

      return nullptr;
    }
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
