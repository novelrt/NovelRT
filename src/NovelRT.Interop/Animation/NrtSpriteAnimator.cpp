// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Animation/NrtAnimatorPlayState.h"
#include "NovelRT.Interop/Animation/NrtSpriteAnimatorState.h"
#include "NovelRT.Interop/NrtNovelRunner.h"
#include "NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h"
#include "NovelRT.Interop/Animation/NrtSpriteAnimator.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t Nrt_SpriteAnimator_create(NrtNovelRunner runner, NrtImageRect rect, NrtSpriteAnimator* outputAnimator) {
    if (runner == nullptr || rect == nullptr || outputAnimator == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* animator = new Animation::SpriteAnimator(reinterpret_cast<NovelRunner*>(runner), reinterpret_cast<Graphics::ImageRect*>(rect));
    *outputAnimator = reinterpret_cast<NrtSpriteAnimator>(animator);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimator_play(NrtSpriteAnimator animator) {
    if (animator == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
    cppAnimator->play();
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimator_pause(NrtSpriteAnimator animator) {
    if (animator == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
    cppAnimator->pause();
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimator_stop(NrtSpriteAnimator animator) {
    if (animator == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
    cppAnimator->stop();
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimator_getCurrentPlayState(NrtSpriteAnimator animator, NrtAnimatorPlayState* outputPlayState) {
    if (animator == nullptr || outputPlayState == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
    Animation::AnimatorPlayState state = cppAnimator->getCurrentPlayState();
    *outputPlayState = reinterpret_cast<NrtAnimatorPlayState&>(state);
    return NRT_SUCCESS;
}

int32_t Nrt_SpriteAnimator_insertNewState(NrtSpriteAnimator animator, NrtSpriteAnimatorState state) {
    if (animator == nullptr || state == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_UNKOWN;
    }

    Animation::SpriteAnimator* cppAnimator = reinterpret_cast<Animation::SpriteAnimator*>(animator);
    std::shared_ptr<Animation::SpriteAnimatorState> cppState = std::shared_ptr<Animation::SpriteAnimatorState>(reinterpret_cast<Animation::SpriteAnimatorState*>(state));
    cppAnimator->insertNewState(cppState);
    return NRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
