// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../../LifetimeExtender.h"
#include <NovelRT.Interop/Ecs/Graphics/NrtTextureInfo.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Ecs/Ecs.h>

using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Interop;

// TextureInfo is a "shared" object. Its lifetime is managed by ConcurrentLifetime (LifetimeExtender.h),
// which can provide a ConcurrentSharedPtr for the TextureInfo.

NrtResult Nrt_TextureInfo_Destroy(NrtTextureInfoHandle texture)
{
    if (texture == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (!ConcurrentLifetime::Release(reinterpret_cast<TextureInfo*>(texture)))
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }

    return NRT_SUCCESS;
}

char* Nrt_TextureInfo_GetTextureName(NrtTextureInfoHandle texture)
{
    return reinterpret_cast<TextureInfo*>(texture)->textureName.data();
}

uint32_t Nrt_TextureInfo_GetTextureWidth(NrtTextureInfoHandle texture)
{
    return reinterpret_cast<TextureInfo*>(texture)->width;
}

uint32_t Nrt_TextureInfo_GetTextureHeight(NrtTextureInfoHandle texture)
{
    return reinterpret_cast<TextureInfo*>(texture)->height;
}

NrtAtom Nrt_TextureInfo_GetEcsId(NrtTextureInfoHandle texture)
{
    return reinterpret_cast<TextureInfo*>(texture)->ecsId;
}

NrtBool Nrt_TextureInfo_Equals(NrtTextureInfoHandle lhs, NrtTextureInfoHandle rhs)
{
    return *reinterpret_cast<TextureInfo*>(lhs) == *reinterpret_cast<TextureInfo*>(rhs);
}
