// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "../LifetimeExtender.h"
#include <NovelRT.Interop/Input/NrtIInputDevice.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/Input/Input.h>

using namespace NovelRT::Input;
using namespace NovelRT::Interop;

NrtResult Nrt_IInputDevice_Destroy(NrtIInputDeviceHandle device)
{
    if (device == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    if (Lifetime::Release(reinterpret_cast<IInputDevice*>(device)))
    {
        return NRT_SUCCESS;
    }
    else
    {
        Nrt_setErrMsgIsAlreadyDeletedOrRemovedInternal();
        return NRT_FAILURE_ALREADY_DELETED_OR_REMOVED;
    }
}

NrtBool Nrt_IInputDevice_IsKeyPressed(NrtIInputDeviceHandle device, const char* key)
{
    return reinterpret_cast<IInputDevice*>(device)->IsKeyPressed(key);
}

NrtBool Nrt_IInputDevice_IsKeyHeld(NrtIInputDeviceHandle device, const char* key)
{
    return reinterpret_cast<IInputDevice*>(device)->IsKeyHeld(key);
}

NrtBool Nrt_IInputDevice_IsKeyReleased(NrtIInputDeviceHandle device, const char* key)
{
    return reinterpret_cast<IInputDevice*>(device)->IsKeyReleased(key);
}

NrtKeyState Nrt_IInputDevice_GetKeyState(NrtIInputDeviceHandle device, const char* key)
{
    return static_cast<NrtKeyState>(reinterpret_cast<IInputDevice*>(device)->GetKeyState(key));
}

NrtResult Nrt_IInputDevice_AddInputAction(NrtIInputDeviceHandle device,
                                          const char* actionName,
                                          const char* keyIdentifier,
                                          NrtInputActionHandle* outputAction)
{
    if (device == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    try
    {
        auto& action = reinterpret_cast<IInputDevice*>(device)->AddInputAction(actionName, keyIdentifier);
        *outputAction = reinterpret_cast<NrtInputActionHandle>(&action);
        return NRT_SUCCESS;
    }
    catch (const NovelRT::Exceptions::InvalidOperationException&)
    {
        Nrt_setErrMsgIsInvalidOperationInternal();
        return NRT_FAILURE_INVALID_OPERATION;
    }
    catch (...)
    {
        Nrt_setErrMsgErrorUnknownInternal();
        return NRT_FAILURE_UNKNOWN;
    }
}

NrtResult Nrt_IInputDevice_GetAvailableKey(NrtIInputDeviceHandle device,
                                           const char* requestedKey,
                                           NrtNovelKeyHandle* outputKey)
{
    if (device == nullptr)
    {
        Nrt_setErrMsgIsNullInstanceProvidedInternal();
        return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
    }

    try
    {
        auto& key = reinterpret_cast<IInputDevice*>(device)->GetAvailableKey(requestedKey);
        *outputKey = reinterpret_cast<NrtNovelKeyHandle>(&key);
        return NRT_SUCCESS;
    }
    catch (const NovelRT::Exceptions::InvalidOperationException&)
    {
        Nrt_setErrMsgIsInvalidOperationInternal();
        return NRT_FAILURE_INVALID_OPERATION;
    }
    catch (...)
    {
        Nrt_setErrMsgErrorUnknownInternal();
        return NRT_FAILURE_UNKNOWN;
    }
}

NrtGeoVector2F Nrt_IInputDevice_GetMousePosition(NrtIInputDeviceHandle device)
{
    NovelRT::Maths::GeoVector2F mousePos = reinterpret_cast<IInputDevice*>(device)->GetMousePosition();
    return reinterpret_cast<NrtGeoVector2F&>(mousePos);
}

NrtInputActionList Nrt_IInputDevice_GetAllMappings(NrtIInputDeviceHandle device)
{
    auto mappings = reinterpret_cast<IInputDevice*>(device)->GetAllMappings();
    return NrtInputActionList{reinterpret_cast<NrtInputActionHandle>(&mappings.back()),
                              reinterpret_cast<NrtInputActionHandle>(&mappings.front()), sizeof(InputAction)};
}
