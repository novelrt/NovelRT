// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSPIPELINEINFO_H
#define NOVELRT_GRAPHICSPIPELINEINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct GraphicsPipelineInfo
    {
        Threading::ConcurrentSharedPtr<NovelRT::Graphics::GraphicsPipeline> gpuPipeline = nullptr;
        Threading::ConcurrentSharedPtr<
            std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>>
            gpuCustomConstantBuffers = nullptr;
        bool useEcsTransforms = false;
        std::string pipelineName = "";
        NovelRT::Core::Atom ecsId = 0;
        uuids::uuid vertexShaderAssetHandle;
        uuids::uuid pixelShaderAssetHandle;
    };
}

#endif // NOVELRT_GRAPHICSPIPELINEINFO_H
