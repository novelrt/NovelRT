// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
#define NOVELRT_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H

#include "NovelRT/Graphics/RGBAConfig.h"
#include <cstdint>

namespace NovelRT::Experimental::Graphics
{
    struct RenderComponent
    {
    public:
        size_t meshDataIndex = 0;
        int32_t renderLayer = 0;
        RGBAConfig colourTint = RGBAConfig(0, 0, 0, 0);
    };

    struct ShaderProgramComponent
    {
    public:
        uint32_t shaderProgramDataIndex = 0;
        int32_t additionalBindingDataIndex = 0;
    };
}

#endif // !NOVELRT_GRAPHICS_ECSDEFAULTRENDERINGCOMPONENTTYPES_H
