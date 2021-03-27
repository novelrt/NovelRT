// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Graphics/NrtRGBAConfig.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRGBAConfigHandle Nrt_RGBAConfig_Create(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        RGBAConfig* newColour = new RGBAConfig(r, g, b, a);

        return reinterpret_cast<NrtRGBAConfigHandle>(newColour);
    }

    int32_t Nrt_RGBAConfig_getR(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getR();
    }

    NrtResult Nrt_RGBAConfig_setR(NrtRGBAConfigHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        colourConfigPtr->setR(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAConfig_getG(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getG();
    }

    NrtResult Nrt_RGBAConfig_setG(NrtRGBAConfigHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        colourConfigPtr->setG(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAConfig_getB(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getB();
    }

    NrtResult Nrt_RGBAConfig_setB(NrtRGBAConfigHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        colourConfigPtr->setB(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAConfig_getA(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getA();
    }

    NrtResult Nrt_RGBAConfig_setA(NrtRGBAConfigHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        colourConfigPtr->setA(inputValue);

        return NRT_SUCCESS;
    }

    float Nrt_RGBAConfig_getRScalar(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getRScalar();
    }

    float Nrt_RGBAConfig_getGScalar(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getGScalar();
    }

    float Nrt_RGBAConfig_getBScalar(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getBScalar();
    }

    float Nrt_RGBAConfig_getAScalar(NrtRGBAConfigHandle colourConfig)
    {
        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);
        return colourConfigPtr->getAScalar();
    }

    NrtResult Nrt_RGBAConfig_destroy(NrtRGBAConfigHandle colourConfig)
    {
        if (colourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        RGBAConfig* colourConfigPtr = reinterpret_cast<RGBAConfig*>(colourConfig);

        delete colourConfigPtr;

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
