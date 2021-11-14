// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSRESOURCEMANAGER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSRESOURCEMANAGER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsResourceManager
    {
    private:
        Utilities::Lazy<std::shared_ptr<GraphicsBuffer>> _stagingBuffer;
        std::vector<std::shared_ptr<GraphicsBuffer>> _vertexBuffers;
        std::shared_ptr<GraphicsDevice> _graphicsDevice;
        size_t _stagingBufferSize;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateStagingBuffer();
        [[nodiscard]] std::shared_ptr<GraphicsBuffer> GetOrCreateGraphicsBufferForAllocationSize(size_t allocationSize);

    public:
        GraphicsResourceManager(std::shared_ptr<GraphicsDevice> graphicsDevice, size_t startingSize = 33554432ULL);
        GraphicsResourceManager(const GraphicsResourceManager& other);
        GraphicsResourceManager(GraphicsResourceManager&& other) noexcept;

        GraphicsResourceManager& operator=(const GraphicsResourceManager& other);
        GraphicsResourceManager& operator=(GraphicsResourceManager&& other) noexcept;

        ~GraphicsResourceManager() = default;

        template<typename TData>
        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadVertexData(gsl::span<TData> data, size_t alignment = 16)
        {
            return LoadVertexDataUntyped(&(*data.begin()), sizeof(TData), data.size(), alignment);
        }

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadVertexDataUntyped(void* data, size_t dataTypeSize, size_t dataLength, size_t alignment);
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSRESOURCEMANAGER_H
