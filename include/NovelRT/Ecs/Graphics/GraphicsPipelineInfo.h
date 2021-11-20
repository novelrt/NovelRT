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
        Experimental::Threading::ConcurrentSharedPtr<Experimental::Graphics::GraphicsPipeline> gpuPipeline = nullptr;
        std::string pipelineName = "";
        Atom ecsId = 0;
    };
}

#endif // NOVELRT_GRAPHICSPIPELINEINFO_H
