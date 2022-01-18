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

    NrtTransform Nrt_BasicFillRect_getTransform(NrtBasicFillRectHandle rect)
    {

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        return *reinterpret_cast<NrtTransform*>(&cppRect->transform());
    }

    NrtResult Nrt_BasicFillRect_setTransform(NrtBasicFillRectHandle rect, NrtTransform inputTransform)
    {
        if (rect == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
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
            return Nrt_getNullInstanceErrorInternal();
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
            return Nrt_getNullInstanceErrorInternal();
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
            return Nrt_getNullInstanceErrorInternal();
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->executeObjectBehaviour();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_getColourConfig(NrtBasicFillRectHandle rect, NrtRGBAColourHandle* outputColourConfig)
    {
        if (rect == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        auto colourConfig = new RGBAColour(0, 0, 0, 0);
        *colourConfig = cppRect->getColourConfig();
        *outputColourConfig = reinterpret_cast<NrtRGBAColourHandle>(colourConfig);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_setColourConfig(NrtBasicFillRectHandle rect, NrtRGBAColourHandle inputColourConfig)
    {
        if (rect == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        BasicFillRect* cppRect = reinterpret_cast<BasicFillRect*>(rect);
        cppRect->setColourConfig(*reinterpret_cast<RGBAColour*>(inputColourConfig));

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_getAsRenderObjectPtr(NrtBasicFillRectHandle rect,
                                                     NrtRenderObjectHandle* outputRenderObject)
    {
        if (rect == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (outputRenderObject == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        *outputRenderObject = reinterpret_cast<NrtRenderObjectHandle>(rect);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_BasicFillRect_destroy(NrtBasicFillRectHandle rect)
    {
        if (rect == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        delete reinterpret_cast<BasicFillRect*>(rect);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
