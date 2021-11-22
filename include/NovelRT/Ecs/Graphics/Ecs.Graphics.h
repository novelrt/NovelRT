// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_H
#define NOVELRT_ECS_GRAPHICS_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

// Ecs.Graphics Dependencies
#include "../../Graphics/RGBAColour.h"

namespace NovelRT::Ecs::Graphics
{
    class DefaultRenderingSystem;
    struct RenderComponent;
    struct GraphicsPipelineComponent;
    struct TextureInfo;
    struct GraphicsPrimitiveInfo;
    struct VertexInfo;
    struct AttachRenderToExistingEntityRequestInfo;
    struct GraphicsPipelineInfo;
    struct CreateRenderEntityRequestInfo;
}

// clang-format off
#include "GraphicsPrimitiveInfo.h"
#include "AttachRenderToExistingEntityRequestInfo.h"
#include "CreateRenderEntityRequestInfo.h"
#include "TextureInfo.h"
#include "VertexInfo.h"
#include "DefaultRenderingSystem.h"
#include "DefaultRenderingComponentTypes.h"
#include "GraphicsPrimitiveInfo.h"
#include "GraphicsPipelineInfo.h"
// clang-format on

#endif // NOVELRT_ECS_GRAPHICS_H
