// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H
#define NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H

#include <vector>
#include <cstdint>

namespace NovelRT::Experimental::Graphics
{
    struct ShaderProgram
    {
        uint32_t shaderProgramId = 0;
        uint32_t viewMatrixUboId = 0;
        uint32_t projectionMatrixUboId = 0;
        std::vector<uint32_t> uboIds = std::vector<uint32_t>{};
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H
