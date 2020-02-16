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
    std::map<std::string, std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>> _transitions;

  public:
    inline void insertNewState(const std::string& transitionName, std::shared_ptr<SpriteAnimatorState> stateTarget, std::vector<std::function<bool()>> transitionConditions) {
      _transitions.try_emplace(transitionName, make_tuple(stateTarget, transitionConditions));
    }

    inline void removeState(const std::string& name) { //not sure if we can make this noexcept somehow but whatever
      _transitions.erase(name);
    }
  };
}

#endif //!NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
