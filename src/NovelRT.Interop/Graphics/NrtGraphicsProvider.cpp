// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/Graphics/NrtGraphicsProvider.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Graphics/Graphics.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Interop;

NrtResult Nrt_GraphicsProvider_Destroy(NrtGraphicsProviderHandle provider)
{
    if (provider == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (Lifetime::Release(reinterpret_cast<GraphicsProvider*>(provider)))
    {
        return NRT_SUCCESS;
    }
    else
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
}
