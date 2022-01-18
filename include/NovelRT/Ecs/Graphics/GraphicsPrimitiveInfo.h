// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSPRIMITIVEINFO_H
#define NOVELRT_GRAPHICSPRIMITIVEINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct GraphicsPrimitiveInfo
    {
        Atom ecsVertexDataId = 0;
        Atom ecsTextureId = 0;
        Atom ecsPipelineId = 0;
        std::map<size_t, Experimental::Graphics::GraphicsMemoryRegion<Experimental::Graphics::GraphicsResource>>
            gpuTransformConstantBufferRegions = {};

        inline bool operator==(const GraphicsPrimitiveInfo& other) const noexcept
        {
            return (ecsVertexDataId == other.ecsVertexDataId) && (ecsTextureId == other.ecsTextureId) &&
                   (ecsPipelineId == other.ecsPipelineId);
        }

        inline bool operator==(const RenderComponent& other) const noexcept
        {
            return (ecsVertexDataId == other.vertexDataId) && (ecsTextureId == other.textureId) &&
                   (ecsPipelineId == other.pipelineId);
        }

        inline bool operator!=(const GraphicsPrimitiveInfo& other) const noexcept
        {
            return !(*this == other);
        }
    };
}

#endif // NOVELRT_GRAPHICSPRIMITIVEINFO_H
