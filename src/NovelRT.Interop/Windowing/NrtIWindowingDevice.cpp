// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Windowing/NrtIWindowingDevice.h>
#include <NovelRT/Windowing/Windowing.h>

using namespace NovelRT::Interop;
using namespace NovelRT::Windowing;

NrtResult Nrt_IWindowingDevice_Destroy(NrtIWindowingDeviceHandle device)
{
    if (device == nullptr)
    {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (Lifetime::Release(reinterpret_cast<IWindowingDevice*>(device)))
    {
        return NRT_SUCCESS;
    }
    else
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
}

NrtBool Nrt_IWindowingDevice_GetIsVisible(NrtIWindowingDeviceHandle device)
{
    return reinterpret_cast<IWindowingDevice*>(device)->GetIsVisible();
}

NrtBool Nrt_IWindowingDevice_GetShouldClose(NrtIWindowingDeviceHandle device)
{
    return reinterpret_cast<IWindowingDevice*>(device)->GetShouldClose();
}

char* Nrt_IWindowingDevice_GetWindowTitle(NrtIWindowingDeviceHandle device)
{
    auto title = reinterpret_cast<IWindowingDevice*>(device)->GetWindowTitle();

    size_t size = strlen(title.c_str()) + 1;
    char* result = reinterpret_cast<char*>(malloc(size));
    strcpy_s(result, size, title.c_str());

    return result;
}

NrtResult Nrt_IWindowingDevice_SetWindowTitle(NrtIWindowingDeviceHandle device, const char* newTitle)
{
    if (device == nullptr) {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    reinterpret_cast<IWindowingDevice*>(device)->SetWindowTitle(newTitle);

    return NRT_SUCCESS;
}

NrtResult Nrt_IWindowingDevice_ProcessAllMessages(NrtIWindowingDeviceHandle device)
{
    if (device == nullptr) {
        Nrt_setErrIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    reinterpret_cast<IWindowingDevice*>(device)->ProcessAllMessages();

    return NRT_SUCCESS;
}
