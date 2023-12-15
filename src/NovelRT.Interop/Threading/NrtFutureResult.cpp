// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include "NovelRT.Interop/NrtErrorHandling.h"
#include <NovelRT.Interop/Threading/NrtFutureResult.h>
#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Threading/Threading.h>

using namespace NovelRT::Threading;

/*
 * FutureResults are implemented in a similar fashion to Events, but in a much simpler way.
 * An NrtFutureResultOfXHandle is simply a pointer to a C++ FutureResult, copied to the heap.
 * Until the NrtFutureResult is destroyed, it holds a reference to the ConcurrentSharedPtr,
 * keeping it alive.
 * Once the value is requested, a "global" reference to X is added using the Lifetime system
 * (see LifetimeExtender.h). It is the user's responsibility to remove this reference by calling
 * the Destroy method on the instance of X, which usually calls Lifetime::Release.
 *
 * Each NrtFutureResultOfX requires two functions (NrtFutureResultOfXHandle = FRH for conciseness):
 * - NrtResult Destroy(FRH future)
 *      Destroys the future result, removing one reference count.
 * - NrtBool TryGetValue(FRH future, XHandle* outValue)
 *      If the value exists:
 *          If outValue is not null:
 *              Write the value handle to outValue
 *              Add a ref count using ConcurrentLifetime (see LifetimeExtender.h)
 *          Return true.
 *      If it doesn't exist: Return false.
 *
 * You can use the GenericFutureResult methods to implement those functions.
 * */

template<typename X> NrtResult GenericFutureResultDestroy(void* handle)
{
    if (handle == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    delete reinterpret_cast<FutureResult<X>*>(handle);
    return NRT_SUCCESS;
}

template<typename X, typename XHandle> NrtBool GenericFutureResultTryGetValue(void* handle, XHandle* outValue)
{
    auto future = reinterpret_cast<FutureResult<X>*>(handle);

    if (future->IsValueCreated())
    {
        if (outValue != nullptr)
        {
            ConcurrentSharedPtr<X> sharedPtr = future->GetBackingConcurrentSharedPtr();

            *outValue = reinterpret_cast<XHandle>(sharedPtr.get());
            NovelRT::Interop::ConcurrentLifetime::KeepAlive(std::move(sharedPtr));
        }
        return true;
    }
    else
    {
        return false;
    }
}

using TextureInfo = NovelRT::Ecs::Graphics::TextureInfo;

NrtResult Nrt_FutureResultOfTextureInfo_Destroy(NrtFutureResultOfTextureInfoHandle handle)
{
    return GenericFutureResultDestroy<TextureInfo>(handle);
}
NrtBool Nrt_FutureResultOfTextureInfo_TryGetValue(NrtFutureResultOfTextureInfoHandle handle,
                                                  NrtTextureInfoHandle* outValue)
{
    return GenericFutureResultTryGetValue<TextureInfo, NrtTextureInfoHandle>(handle, outValue);
}
