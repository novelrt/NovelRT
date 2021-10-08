// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_H
#define NOVELRT_ECS_GRAPHICS_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    class DefaultEcsRenderingSystem;
    struct RenderComponent;
    struct GraphicsPipelineComponent;
}

// clang-format off
#include "DefaultRenderingSystem.h"
#include "DefaultRenderingComponentTypes.h"
// clang-format on

#endif // NOVELRT_ECS_GRAPHICS_H
