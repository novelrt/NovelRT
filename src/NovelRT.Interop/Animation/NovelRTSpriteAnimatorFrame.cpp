// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Graphics/NovelRTGraphicsTypedefs.h"
#include "NovelRT.Interop/Animation/NovelRTSpriteAnimatorFrame.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTSpriteAnimatorFrame NovelRT_SpriteAnimatorFrame_create() {
    Animation::SpriteAnimatorFrame* frame = new Animation::SpriteAnimatorFrame();
    return reinterpret_cast<NovelRTSpriteAnimatorFrame>(frame);
}

int32_t NovelRT_SpriteAnimatorFrame_getTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture* outputTexture, const char** errorMessage) {
    if (frame == nullptr || outputTexture == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    std::shared_ptr<Graphics::Texture> cppTexture = cppFrame->texture();
    
    *outputTexture = reinterpret_cast<NovelRTTexture>(cppTexture.get());
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrame_setTexture(NovelRTSpriteAnimatorFrame frame, NovelRTTexture texture, const char** errorMessage) {
    if (frame == nullptr || texture == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppFrame->texture() = reinterpret_cast<Graphics::Texture*>(texture)->shared_from_this();
    
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrame_getDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp* outputTimestamp, const char** errorMessage) {
    if (frame == nullptr || outputTimestamp == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    Timing::Timestamp* cppDuration = new Timing::Timestamp(0);
    *cppDuration = cppFrame->duration();
    
    *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&*cppDuration);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrame_setDuration(NovelRTSpriteAnimatorFrame frame, NovelRTTimestamp timestamp, const char** errorMessage) {
    if (frame == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppFrame->duration() = reinterpret_cast<Timing::Timestamp&>(timestamp);
    
    return NOVELRT_SUCCESS;
}


int32_t NovelRT_SpriteAnimatorFrame_addFrameEnter(NovelRTSpriteAnimatorFrame frame, void(*func)(), const char** errorMessage) {
    if (frame == nullptr || func == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppFrame->FrameEnter += func;
    
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_SpriteAnimatorFrame_addFrameExit(NovelRTSpriteAnimatorFrame frame, void(*func)(), const char** errorMessage) {
    if (frame == nullptr || func == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
    cppFrame->FrameExit += func;
    
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
