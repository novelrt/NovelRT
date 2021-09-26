// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_SHADERPROGRAM_H
#define NOVELRT_GRAPHICS_SHADERPROGRAM_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics
{
    struct ShaderProgram
    {
    public:
        GLuint shaderProgramId = 0;
        GLuint finalViewMatrixBufferUboId = 0;
        std::vector<GLuint> uboIds;

        ShaderProgram() = default;
    };
} // namespace NovelRT::Graphics

#endif
