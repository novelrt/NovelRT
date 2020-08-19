// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Input/NovelRTBasicInteractionRect.h"
#include "NovelRT.Interop/NovelRTTransform.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NovelRTResult NovelRT_Input_BasicInteractionRect_executeObjectBehaviour(NovelRTBasicInteractionRect object, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->executeObjectBehaviour();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_getTransform(NovelRTBasicInteractionRect object, NovelRTTransform* outputTransform, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputTransform = reinterpret_cast<NovelRTTransform&>(obj->transform());
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_setTransform(NovelRTBasicInteractionRect object, NovelRTTransform transform, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->transform() = reinterpret_cast<Transform&>(transform);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_getLayer(NovelRTBasicInteractionRect object, int* outputValue, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->layer();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_setLayer(NovelRTBasicInteractionRect object, int value, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->layer() = value;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_getActive(NovelRTBasicInteractionRect object, NovelRTBool* outputValue, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = obj->getActive();
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_setActive(NovelRTBasicInteractionRect object, NovelRTBool value, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->setActive(value);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_getSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode* outputValue, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    *outputValue = reinterpret_cast<NovelRTKeyCode&>(obj->subscribedKey());
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_setSubscribedKey(NovelRTBasicInteractionRect object, NovelRTKeyCode value, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    obj->subscribedKey() = reinterpret_cast<Input::KeyCode&>(value);
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_addInteraction(NovelRTBasicInteractionRect object, FunctionPointer ptr, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    std::function<void()> functionPtr = reinterpret_cast<std::function<void()>&>(ptr);
    obj->Interacted += functionPtr;
    return NOVELRT_SUCCESS;
}

NovelRTResult NovelRT_Input_BasicInteractionRect_addInteraction(NovelRTBasicInteractionRect object, FunctionPointer ptr, const char** errorMessage) {
    if (object == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = NovelRT_getErrMsgIsNullptr();
        }
        return NOVELRT_FAILURE;
    }

    auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
    std::function<void()> functionPtr = reinterpret_cast<std::function<void()>&>(ptr);
    obj->Interacted -= functionPtr;
    return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

