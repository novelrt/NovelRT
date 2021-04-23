// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H
#define NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H

#include "GraphicsDeviceObject.h"
#include <cstdint>
#include <gsl/span>
#include <vector>
#include <string>

namespace NovelRT::Experimental::Graphics
{
    class ShaderProgram : public GraphicsDeviceObject
    {
    private:
        std::string _entryPointName;

    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_SHADERPROGRAM_H
