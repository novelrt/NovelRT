// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_METAL_UTILITIES_H
#define NOVELRT_GRAPHICS_METAL_UTILITIES_H

#ifdef TARGET_OS_MAC

#ifndef NOVELRT_GRAPHICS_METAL_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.Metal.h instead for the Graphics::Metal namespace subset.
#endif

#include "PipelineBlendFactor.h"

#endif // TARGET_OS_MAC

#endif // !NOVELRT_GRAPHICS_METAL_UTILITIES_H
