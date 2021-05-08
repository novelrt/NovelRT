// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Input/NrtBasicInteractionRect.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtResult Nrt_Input_BasicInteractionRect_executeObjectBehaviour(NrtBasicInteractionRectHandle object)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->executeObjectBehaviour();
        return NRT_SUCCESS;
    }

    NrtTransform Nrt_Input_BasicInteractionRect_getTransform(NrtBasicInteractionRectHandle object)
    {
        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        return reinterpret_cast<NrtTransform&>(obj->transform());
    }

    NrtResult Nrt_Input_BasicInteractionRect_setTransform(NrtBasicInteractionRectHandle object, NrtTransform transform)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->transform() = reinterpret_cast<Transform&>(transform);
        return NRT_SUCCESS;
    }

    int32_t Nrt_Input_BasicInteractionRect_getLayer(NrtBasicInteractionRectHandle object)
    {
        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        return obj->layer();
    }

    NrtResult Nrt_Input_BasicInteractionRect_setLayer(NrtBasicInteractionRectHandle object, int32_t value)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->layer() = value;
        return NRT_SUCCESS;
    }

    int32_t Nrt_Input_BasicInteractionRect_getActive(NrtBasicInteractionRectHandle object)
    {
        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        return obj->getActive() ? NRT_TRUE : NRT_FALSE;
    }

    NrtResult Nrt_Input_BasicInteractionRect_setActive(NrtBasicInteractionRectHandle object, int32_t value)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->setActive(value);
        return NRT_SUCCESS;
    }

    NrtKeyCode Nrt_Input_BasicInteractionRect_getSubscribedKey(NrtBasicInteractionRectHandle object)
    {
        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        return reinterpret_cast<NrtKeyCode&>(obj->subscribedKey());
    }

    NrtResult Nrt_Input_BasicInteractionRect_setSubscribedKey(NrtBasicInteractionRectHandle object, NrtKeyCode value)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->subscribedKey() = reinterpret_cast<Input::KeyCode&>(value);
        return NRT_SUCCESS;
    }

    NrtResult Nrt_Input_BasicInteractionRect_addInteraction(NrtBasicInteractionRectHandle object,
                                                            void (*action)(void*),
                                                            void* context)
    {
        if (object == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (action == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        auto obj = reinterpret_cast<Input::BasicInteractionRect*>(object);
        obj->Interacted += std::bind(action, context);
        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
