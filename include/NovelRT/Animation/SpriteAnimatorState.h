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

  public:
    std::map<std::string, std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>> transitions; //fuck I give up for now

    inline void insertNewState(const std::string& transitionName, std::shared_ptr<SpriteAnimatorState> stateTarget, std::vector<std::function<bool()>> transitionConditions) {
      transitions.try_emplace(transitionName, make_tuple(stateTarget, transitionConditions));
    }

    inline void removeState(const std::string& name) { //not sure if we can make this noexcept somehow but whatever
      transitions.erase(name);
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

    inline void setTransitions(const std::map<std::string, std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>>& value) noexcept {
      transitions = value;
    }
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
