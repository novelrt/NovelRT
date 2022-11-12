// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSRESOURCEMANAGER_H
#define NOVELRT_GRAPHICS_GRAPHICSRESOURCEMANAGER_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsResourceManager
    {
    private:
        Utilities::Lazy<std::shared_ptr<GraphicsBuffer>> _stagingBuffer;
        std::vector<std::shared_ptr<GraphicsBuffer>> _defaultBuffers;
        std::vector<std::shared_ptr<GraphicsBuffer>> _vertexBuffers;
        std::vector<std::shared_ptr<GraphicsBuffer>> _indexBuffers;
        std::vector<std::shared_ptr<GraphicsBuffer>> _constantBuffers;
        std::vector<std::shared_ptr<GraphicsTexture>> _textures;
        std::set<size_t> _constantBuffersToUnmapAndWrite;
        std::shared_ptr<GraphicsDevice> _graphicsDevice;
        size_t _stagingBufferSize;
        static constexpr size_t _tenMegabytesAsBytes = 10 * 1024 * 1024;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateStagingBuffer();
        [[nodiscard]] std::shared_ptr<GraphicsBuffer> GetOrCreateGraphicsBufferForAllocationSize(size_t allocationSize, GraphicsBufferKind bufferKind);
        [[nodiscard]] std::shared_ptr<GraphicsBuffer> GetStagingBufferWithProperSizeHandling(
            size_t sizeToStage,
            std::shared_ptr<GraphicsContext>& currentContext);

    public:
        explicit GraphicsResourceManager(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                         size_t startingStagingBufferSize = 0);
        GraphicsResourceManager(const GraphicsResourceManager& other);
        GraphicsResourceManager(GraphicsResourceManager&& other) noexcept;

        GraphicsResourceManager& operator=(const GraphicsResourceManager& other);
        GraphicsResourceManager& operator=(GraphicsResourceManager&& other) noexcept;

        ~GraphicsResourceManager() = default;

        template<typename TData>
        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadVertexData(gsl::span<TData> data, size_t alignment = 0)
        {
            return LoadVertexDataUntyped(&(*data.begin()), sizeof(TData), data.size(), alignment);
        }

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadVertexDataUntyped(void* data,
                                                                                   size_t dataTypeSize,
                                                                                   size_t dataLength,
                                                                                   size_t alignment = 16);

        template<typename TData>
        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadIndexData(gsl::span<TData> data, size_t alignment = 0)
        {
            return LoadIndexDataUntyped(&(*data.begin()), sizeof(TData), data.size(), alignment);
        }

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadIndexDataUntyped(void* data,
                                                                                   size_t dataTypeSize,
                                                                                   size_t dataLength,
                                                                                   size_t alignment = 64);

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadTextureData(
            const ResourceManagement::TextureMetadata& metadata,
            GraphicsTextureAddressMode addressMode,
            GraphicsTextureKind textureKind);

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> AllocateConstantBufferRegion(size_t size,
                                                                                          size_t alignment = 256);

        [[nodiscard]] GraphicsMemoryRegion<GraphicsResource> LoadConstantBufferDataToNewRegion(void* data,
                                                                                               size_t size,
                                                                                               size_t alignment = 256);

        void LoadConstantBufferDataToExistingRegion(GraphicsMemoryRegion<GraphicsResource>& targetMemoryResource,
                                                    void* data,
                                                    size_t size);
        [[nodiscard]] uint8_t* MapConstantBufferRegionForWritingUntyped(
            GraphicsMemoryRegion<GraphicsResource>& targetMemoryResource);

        template<typename TPointerType>
        [[nodiscard]] TPointerType* MapConstantBufferRegionForWriting(
            GraphicsMemoryRegion<GraphicsResource>& targetMemoryResource)
        {
            return reinterpret_cast<TPointerType*>(MapConstantBufferRegionForWritingUntyped(targetMemoryResource));
        }
        void UnmapAndWriteAllConstantBuffers() noexcept;

        void FreeConstantBufferData(GraphicsMemoryRegion<GraphicsResource>& regionToFree);
        void FreeVertexData(GraphicsMemoryRegion<GraphicsResource>& vertexResource);
        void FreeIndexData(GraphicsMemoryRegion<GraphicsResource>& indexResource);
        void FreeTextureData(GraphicsMemoryRegion<GraphicsResource>& textureResource);

    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSRESOURCEMANAGER_H
