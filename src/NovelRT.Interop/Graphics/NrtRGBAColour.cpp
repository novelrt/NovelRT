// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtRGBAColour.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtRGBAColourHandle Nrt_RGBAColour_Create(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        RGBAColour* newColour = new RGBAColour(r, g, b, a);

        return reinterpret_cast<NrtRGBAColourHandle>(newColour);
    }

    int32_t Nrt_RGBAColour_getR(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getR();
    }

    NrtResult Nrt_RGBAColour_setR(NrtRGBAColourHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        colourConfigPtr->setR(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAColour_getG(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getG();
    }

    NrtResult Nrt_RGBAColour_setG(NrtRGBAColourHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        colourConfigPtr->setG(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAColour_getB(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getB();
    }

    NrtResult Nrt_RGBAColour_setB(NrtRGBAColourHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        colourConfigPtr->setB(inputValue);

        return NRT_SUCCESS;
    }

    int32_t Nrt_RGBAColour_getA(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getA();
    }

    NrtResult Nrt_RGBAColour_setA(NrtRGBAColourHandle colourConfig, int32_t inputValue)
    {
        if (colourConfig == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        colourConfigPtr->setA(inputValue);

        return NRT_SUCCESS;
    }

    float Nrt_RGBAColour_getRScalar(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getRScalar();
    }

    float Nrt_RGBAColour_getGScalar(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getGScalar();
    }

    float Nrt_RGBAColour_getBScalar(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getBScalar();
    }

    float Nrt_RGBAColour_getAScalar(NrtRGBAColourHandle colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);
        return colourConfigPtr->getAScalar();
    }

    NrtResult Nrt_RGBAColour_destroy(NrtRGBAColourHandle colourConfig)
    {
        if (colourConfig == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(colourConfig);

        delete colourConfigPtr;

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
