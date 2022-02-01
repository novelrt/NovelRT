// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_VERTEXINFO_H
#define NOVELRT_ECS_GRAPHICS_VERTEXINFO_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    struct VertexInfo
    {
        NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource> gpuVertexRegion = {};
        std::string vertexInfoName;
        Atom ecsId = 0;
        void* stagingPtr = nullptr;
        size_t sizeOfVert = 0;
        size_t stagingPtrLength = 0;
        uint32_t stride = 0;

        bool operator==(const VertexInfo& other) const noexcept
        {
            return (gpuVertexRegion == other.gpuVertexRegion) && (vertexInfoName == other.vertexInfoName) &&
                   (ecsId == other.ecsId);
        }
    };
}

#endif // NOVELRT_ECS_GRAPHICS_VERTEXINFO_H
