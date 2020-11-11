// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Input/NrtBasicInteractionRect.h"
#include "NovelRT.Interop/NrtTransform.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRect object) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->executeObjectBehaviour();
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRect object, NrtTransform* outputTransform) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputTransform = reinterpret_cast<NrtTransform&>(obj->transform());
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRect object, NrtTransform transform) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->transform() = reinterpret_cast<Transform&>(transform);
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRect object, int* outputValue) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->layer();
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRect object, int value) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->layer() = value;
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRect object, int32_t* outputValue) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->getActive()? NRT_TRUE : NRT_FALSE;
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRect object, int32_t value) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->setActive(value);
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRect object, NrtKeyCodeKind* outputValue) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = reinterpret_cast<NrtKeyCodeKind&>(obj->subscribedKey());
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRect object, NrtKeyCodeKind value) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->subscribedKey() = reinterpret_cast<Input::KeyCode&>(value);
    return NRT_SUCCESS;
}

NrtResult Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRect object, void(*ptr)()) {
    if (object == nullptr) {
        Nrt_setErrMsgIsNullptrInternal();
        return NRT_FAILURE_NULLPTR_PROVIDED;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->Interacted += ptr;
    return NRT_SUCCESS;
}

// NrtResult Nrt_Input_BasicInteractionRect_removeInteraction(NrtBasicInteractionRect object, FunctionPointer ptr) {
//     if (object == nullptr) {
//         if (errorMessage != nullptr) {
//             *errorMessage = Nrt_getErrMsgIsNullptr();
//         }
//         return NOVELRT_FAILURE;
//     }

//     auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
//     std::function<void()> functionPtr = reinterpret_cast<std::function<void()>&>(ptr);
//     obj->Interacted -= functionPtr;
//     return NOVELRT_SUCCESS;
// }

#ifdef __cplusplus
}
#endif

