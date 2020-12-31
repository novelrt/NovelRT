// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Animation/NrtSpriteAnimatorFrame.h>
#include <NovelRT.Interop/Graphics/NrtGraphicsTypedefs.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.Interop/NrtInteropUtils.h>
#include <NovelRT.Interop/Timing/NrtTimestamp.h>
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtSpriteAnimatorFrame Nrt_SpriteAnimatorFrame_create()
    {
        Animation::SpriteAnimatorFrame* frame = new Animation::SpriteAnimatorFrame();
        return reinterpret_cast<NrtSpriteAnimatorFrame>(frame);
    }

    NrtResult Nrt_SpriteAnimatorFrame_getTexture(NrtSpriteAnimatorFrame frame, NrtTexture* outputTexture)
    {
        if (frame == nullptr || outputTexture == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        std::shared_ptr<Graphics::Texture> cppTexture = cppFrame->texture();

        *outputTexture = reinterpret_cast<NrtTexture>(cppTexture.get());
        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimatorFrame_setTexture(NrtSpriteAnimatorFrame frame, NrtTexture texture)
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

    NrtTimestamp Nrt_SpriteAnimatorFrame_getDuration(NrtSpriteAnimatorFrame frame)
    {
        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        Timing::Timestamp* cppDuration = new Timing::Timestamp(0);
        *cppDuration = cppFrame->duration();

        return reinterpret_cast<NrtTimestamp&>(*cppDuration);
    }

    NrtResult Nrt_SpriteAnimatorFrame_setDuration(NrtSpriteAnimatorFrame frame, NrtTimestamp timestamp)
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

    NrtResult Nrt_SpriteAnimatorFrame_addFrameEnter(NrtSpriteAnimatorFrame frame, void (*func)())
    {
        if (frame == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->FrameEnter += func;

        return NRT_SUCCESS;
    }

    NrtResult Nrt_SpriteAnimatorFrame_addFrameExit(NrtSpriteAnimatorFrame frame, void (*func)())
    {
        if (frame == nullptr || func == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Animation::SpriteAnimatorFrame* cppFrame = reinterpret_cast<Animation::SpriteAnimatorFrame*>(frame);
        cppFrame->FrameExit += func;

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
