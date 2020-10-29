// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Input/NovelRTBasicInteractionRect.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

int32_t NovelRT_Input_BasicInteractionRect_executeObjectBehaviour(NovelRTBasicInteractionRect object) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->executeObjectBehaviour();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_getTransform(NovelRTBasicInteractionRect object, NovelRTTransform* outputTransform) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputTransform = reinterpret_cast<NovelRTTransform&>(obj->transform());
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_setTransform(NovelRTBasicInteractionRect object, NovelRTTransform transform) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->transform() = reinterpret_cast<Transform&>(transform);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_getLayer(NovelRTBasicInteractionRect object, int* outputValue) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->layer();
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_setLayer(NovelRTBasicInteractionRect object, int value) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->layer() = value;
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_getActive(NovelRTBasicInteractionRect object, int32_t* outputValue) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->getActive()? NOVELRT_TRUE : NOVELRT_FALSE;
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_setActive(NovelRTBasicInteractionRect object, int32_t value) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->setActive(value);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_getSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode* outputValue) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = reinterpret_cast<NovelRTKeyCode&>(obj->subscribedKey());
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_setSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode value) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->subscribedKey() = reinterpret_cast<Input::KeyCode&>(value);
    return NOVELRT_SUCCESS;
}

int32_t NovelRT_Input_BasicInteractionRect_addInteraction(NovelRTBasicInteractionRect object, void(*ptr)()) {
    if (object == nullptr) {
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->Interacted += ptr;
    return NOVELRT_SUCCESS;
}

// int32_t NovelRT_Input_BasicInteractionRect_removeInteraction(NovelRTBasicInteractionRect object, FunctionPointer ptr) {
//     if (object == nullptr) {
//         if (errorMessage != nullptr) {
//             *errorMessage = NovelRT_getErrMsgIsNullptr();
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

