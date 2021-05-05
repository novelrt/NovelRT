// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtBasicFillRect.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Graphics;

// COSPLAY
#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_BasicFillRect_getTransform(NrtBasicFillRectHandle rect, NrtTransform* outputTransform)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        *outputTransform = *reinterpret_cast<NrtTransform*>(&cppRect->transform());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_setTransform(NrtBasicFillRectHandle rect, NrtTransform inputTransform)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->transform() = *reinterpret_cast<Transform*>(&inputTransform);

        return NRT_SUCCESS;
    }

    int32_t Nrt_BasicFillRect_getLayer(NrtBasicFillRectHandle rect)
    {
        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        return cppRect->layer();
    }

    NrtResult Nrt_BasicFillRect_setLayer(NrtBasicFillRectHandle rect, int32_t inputLayer)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->layer() = inputLayer;

        return NRT_SUCCESS;
    }

    NrtBool Nrt_BasicFillRect_getActive(NrtBasicFillRectHandle rect)
    {
        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        if (cppRect->getActive())
        {
            return NRT_TRUE;
        }
        return NRT_FALSE;
    }

    NrtResult Nrt_BasicFillRect_setActive(NrtBasicFillRectHandle rect, NrtBool inputBool)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);

        if (inputBool == NRT_TRUE)
        {
            cppRect->setActive(true);
        }
        else
        {
            cppRect->setActive(false);
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_executeObjectBehaviour(NrtBasicFillRectHandle rect)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->executeObjectBehaviour();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_getColourConfig(NrtBasicFillRectHandle rect, NrtRGBAConfigHandle* outputColourConfig)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        auto colourConfig = cppRect->getColourConfig();
        *outputColourConfig = *reinterpret_cast<NrtRGBAConfigHandle*>(&colourConfig);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_setColourConfig(NrtBasicFillRectHandle rect, NrtRGBAConfigHandle inputColourConfig)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->setColourConfig(*reinterpret_cast<RGBAConfig*>(&inputColourConfig));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_getAsRenderObjectPtr(NrtBasicFillRectHandle rect,
                                                     NrtRenderObjectHandle* outputRenderObject)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        *outputRenderObject = reinterpret_cast<NrtRenderObjectHandle>(rect);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
