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

    float Nrt_RGBAColour_getRScalar(NrtRGBAColour colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(&colourConfig);
        return colourConfigPtr->getRScalar();
    }

    float Nrt_RGBAColour_getGScalar(NrtRGBAColour colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(&colourConfig);
        return colourConfigPtr->getGScalar();
    }

    float Nrt_RGBAColour_getBScalar(NrtRGBAColour colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(&colourConfig);
        return colourConfigPtr->getBScalar();
    }

    float Nrt_RGBAColour_getAScalar(NrtRGBAColour colourConfig)
    {
        RGBAColour* colourConfigPtr = reinterpret_cast<RGBAColour*>(&colourConfig);
        return colourConfigPtr->getAScalar();
    }

#ifdef __cplusplus
}
#endif
