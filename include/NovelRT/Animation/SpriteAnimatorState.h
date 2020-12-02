// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
#define NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Animation
{
class SpriteAnimatorState
{
  private:
    std::vector<SpriteAnimatorFrame> _frames;
    bool _shouldLoop = false; // this is to shut the warning up since we have no ctor
    std::vector<std::tuple<std::shared_ptr<SpriteAnimatorState>, std::vector<std::function<bool()>>>> _transitions;

  public:
    inline void insertNewState(std::shared_ptr<SpriteAnimatorState> stateTarget,
                               std::vector<std::function<bool()>> transitionConditions)
    {

        if (stateTarget == nullptr)
        {
            return;
        }

        for (size_t i = 0; i < transitionConditions.size(); i++)
        {
            if (transitionConditions.at(i) == nullptr)
            {
                transitionConditions.erase(transitionConditions.begin() +
                                           static_cast<std::vector<SpriteAnimatorFrame>::iterator::difference_type>(i));
            }
        }

        _transitions.emplace_back(make_tuple(stateTarget, transitionConditions));
    }

    inline void removeStateAtIndex(size_t index)
    { // not sure if we can make this noexcept somehow but whatever
        _transitions.erase(_transitions.begin() + index);
    }

    inline const bool &shouldLoop() const noexcept
    {
        return _shouldLoop;
    }

    inline bool &shouldLoop() noexcept
    {
        return _shouldLoop;
    }

    inline const std::vector<SpriteAnimatorFrame> &frames() const noexcept
    {
        return _frames;
    }

    inline std::vector<SpriteAnimatorFrame> &frames() noexcept
    {
        return _frames;
    }

    inline std::shared_ptr<SpriteAnimatorState> tryFindValidTransition()
    {
        for (auto transitionTuple : _transitions)
        {
            auto conditions = std::get<std::vector<std::function<bool()>>>(transitionTuple);
            bool shouldTransitionToThisState = true;

            for (auto condition : conditions)
            {
                if (condition())
                    continue;

                shouldTransitionToThisState = false;
                break;
            }

            if (!shouldTransitionToThisState)
                continue;

            return std::get<std::shared_ptr<SpriteAnimatorState>>(transitionTuple);
        }

        return nullptr;
    }
};
} // namespace NovelRT::Animation

#endif //! NOVELRT_ANIMATION_SPRITEANIMATORSTATE_H
