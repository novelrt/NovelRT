// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Animation/NrtSpriteAnimator.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_SpriteAnimator_create(NrtNovelRunnerHandle runner,
                                        NrtImageRectHandle rect,
                                        NrtSpriteAnimatorHandle* outputAnimator)
    {
        if (runner == nullptr || rect == nullptr || outputAnimator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Animation::SpriteAnimator* animator = new Animation::SpriteAnimator(
            reinterpret_cast<NovelRunner*>(runner), reinterpret_cast<Graphics::ImageRect*>(rect));
        *outputAnimator = reinterpret_cast<NrtSpriteAnimatorHandle>(animator);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimator_play(NrtSpriteAnimatorHandle animator)
    {
        if (animator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
        cppAnimator->play();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimator_pause(NrtSpriteAnimatorHandle animator)
    {
        if (animator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
        cppAnimator->pause();
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimator_stop(NrtSpriteAnimatorHandle animator)
    {
        if (animator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
        cppAnimator->stop();
        return NRT_SUCCESS;
    }

    NrtAnimatorPlayState Nrt_SpriteAnimator_getCurrentPlayState(NrtSpriteAnimatorHandle animator)
    {
        Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
        Animation::AnimatorPlayState state = cppAnimator->getCurrentPlayState();
        return reinterpret_cast<NrtAnimatorPlayState&>(state);
    }

    NrtResult Nrt_SpriteAnimator_insertNewState(NrtSpriteAnimatorHandle animator, NrtSpriteAnimatorStateHandle state)
    {
        if (animator == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (state == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
        std::shared_ptr<Animation::SpriteAnimatorState> cppState =
            std::shared_ptr<Animation::SpriteAnimatorState>(reinterpret_cast<Animation::SpriteAnimatorState*>(state));
        cppAnimator->insertNewState(cppState);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
