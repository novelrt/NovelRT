// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Animation/NrtSpriteAnimatorFrame.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtSpriteAnimatorFrameHandle Nrt_SpriteAnimatorFrame_create()
    {
        Animation::SpriteAnimatorFrame* frame = new Animation::SpriteAnimatorFrame();
        return reinterpret_cast<NrtSpriteAnimatorFrameHandle>(frame);
    }

    NrtResult Nrt_SpriteAnimatorFrame_getTexture(NrtSpriteAnimatorFrameHandle frame, NrtTextureHandle* outputTexture)
    {
        if (frame == nullptr || outputTexture == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        std::shared_ptr<Graphics::Texture> cppTexture = cppFrame->texture();

        *outputTexture = reinterpret_cast<NrtTextureHandle>(cppTexture.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimatorFrame_setTexture(NrtSpriteAnimatorFrameHandle frame, NrtTextureHandle texture)
    {
        if (frame == nullptr || texture == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->texture() = reinterpret_cast<Graphics::Texture*>(texture)->shared_from_this();

        return NRT_SUCCESS;
    }

    NrtTimestamp Nrt_SpriteAnimatorFrame_getDuration(NrtSpriteAnimatorFrameHandle frame)
    {
        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        Timing::Timestamp* cppDuration = new Timing::Timestamp(0);
        *cppDuration = cppFrame->duration();

        return reinterpret_cast<NrtTimestamp&>(*cppDuration);
    }

    NrtResult Nrt_SpriteAnimatorFrame_setDuration(NrtSpriteAnimatorFrameHandle frame, NrtTimestamp timestamp)
    {
        if (frame == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->duration() = Timing::Timestamp(timestamp);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimatorFrame_addFrameEnter(NrtSpriteAnimatorFrameHandle frame, void (*func)(void*), void* context)
    {
        if (frame == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->FrameEnter += std::bind(func, context);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimatorFrame_addFrameExit(NrtSpriteAnimatorFrameHandle frame, void (*func)(void*), void* context)
    {
        if (frame == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->FrameExit += std::bind(func, context);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
