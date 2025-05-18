#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/ShaderProgramVisibility.hpp>

namespace NovelRT::Graphics
{
    struct GraphicsPushConstantRange
    {
        ShaderProgramVisibility visibilityFlags = ShaderProgramVisibility::NoneOrUnknown;
        size_t offset = 0;
        size_t size = 0;
    };
}
