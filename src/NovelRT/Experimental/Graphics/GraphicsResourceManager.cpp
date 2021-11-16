// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>
#include <NovelRT/Experimental/Graphics/GraphicsResourceManager.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsResourceManager::GraphicsResourceManager(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                                     size_t startingStagingBufferSize)
        : _graphicsDevice(std::move(graphicsDevice)),
          _stagingBuffer([&]() { return CreateStagingBuffer(); }),
          _stagingBufferSize(startingStagingBufferSize)
    {
        if (_stagingBufferSize == 0)
        {
            _stagingBufferSize = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;
        }
    }

    GraphicsResourceManager::GraphicsResourceManager(const GraphicsResourceManager& other)
        : _graphicsDevice(nullptr), _stagingBuffer(nullptr), _stagingBufferSize(0), _vertexBuffers{}, _textures{}
    {
        *this = other;
    }

    GraphicsResourceManager::GraphicsResourceManager(GraphicsResourceManager&& other) noexcept
        : _graphicsDevice(nullptr), _stagingBuffer(nullptr), _stagingBufferSize(0), _vertexBuffers{}, _textures{}
    {
        *this = std::move(other);
    }

    GraphicsResourceManager& GraphicsResourceManager::operator=(const GraphicsResourceManager& other)
    {
        if (this == &other)
        {
            return *this;
        }

        _graphicsDevice = other._graphicsDevice;
        _stagingBuffer = Utilities::Lazy<std::shared_ptr<GraphicsBuffer>>([&]() { return CreateStagingBuffer(); });
        _stagingBufferSize = other._stagingBufferSize;
        _vertexBuffers = {};
        _textures = {};

        return *this;
    }

    GraphicsResourceManager& GraphicsResourceManager::operator=(GraphicsResourceManager&& other) noexcept
    {
        _graphicsDevice = std::move(other._graphicsDevice);
        _stagingBuffer = Utilities::Lazy<std::shared_ptr<GraphicsBuffer>>([&]() { return CreateStagingBuffer(); });

        if (other._stagingBuffer.isCreated())
        {
            _stagingBuffer.reset(other._stagingBuffer.getActual());
            other._stagingBuffer.reset();
        }

        _vertexBuffers = std::move(other._vertexBuffers);
        _textures = std::move(other._textures);
        _stagingBufferSize = other._stagingBufferSize;
        other._stagingBufferSize = 0;

        return *this;
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::LoadVertexDataUntyped(void* data,
                                                                                          size_t dataTypeSize,
                                                                                          size_t dataLength,
                                                                                          size_t alignment)
    {
        size_t sizeToStage = dataTypeSize * dataLength;
        auto currentContext = _graphicsDevice->GetCurrentContext();

        std::shared_ptr<GraphicsBuffer> stagingBuffer =
            GetStagingBufferWithProperSizeHandling(sizeToStage, currentContext);

        std::shared_ptr<GraphicsBuffer> vertexBuffer = GetOrCreateGraphicsBufferForAllocationSize(sizeToStage);
        auto vertexRegion = vertexBuffer->Allocate(sizeToStage, alignment);
        auto writeArea = stagingBuffer->Map<uint8_t>(vertexRegion);
        memcpy_s(writeArea, sizeToStage, data, sizeToStage);
        stagingBuffer->UnmapAndWrite(vertexRegion);
        currentContext->Copy(vertexBuffer, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        currentContext->BeginFrame();

        return vertexRegion;
    }

    std::shared_ptr<GraphicsBuffer> GraphicsResourceManager::GetStagingBufferWithProperSizeHandling(
        size_t sizeToStage,
        std::shared_ptr<GraphicsContext>& currentContext)
    {
        std::shared_ptr<GraphicsBuffer> stagingBuffer = _stagingBuffer.getActual();

        if (stagingBuffer->GetLargestFreeRegionSize() < sizeToStage)
        {
            _stagingBufferSize = (_stagingBufferSize * 2) + sizeToStage;
            std::shared_ptr<GraphicsBuffer> newStagingBuffer = CreateStagingBuffer();
            currentContext->Copy(newStagingBuffer, stagingBuffer);
            currentContext->EndFrame();
            _graphicsDevice->Signal(currentContext->GetFence());
            _graphicsDevice->WaitForIdle();
            _stagingBuffer.reset(newStagingBuffer);
            stagingBuffer = _stagingBuffer.getActual();
            currentContext->BeginFrame();
        }
        return stagingBuffer;
    }

    std::shared_ptr<GraphicsBuffer> GraphicsResourceManager::CreateStagingBuffer()
    {
        return _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            Experimental::Graphics::GraphicsBufferKind::Default, Experimental::Graphics::GraphicsResourceAccess::Write,
            Experimental::Graphics::GraphicsResourceAccess::Read, _stagingBufferSize);
    }

    std::shared_ptr<GraphicsBuffer> GraphicsResourceManager::GetOrCreateGraphicsBufferForAllocationSize(
        size_t allocationSize)
    {
        for (auto&& buffer : _vertexBuffers)
        {
            if (buffer->GetLargestFreeRegionSize() >= allocationSize)
            {
                return buffer;
            }
        }

        size_t minimumBlockSize = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;
        size_t sizeToAllocate = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;

        while (sizeToAllocate < allocationSize)
        {
            sizeToAllocate += minimumBlockSize;
        }

        // TODO: This needs to be improved.
        auto newBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            GraphicsBufferKind::Vertex, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, sizeToAllocate);

        _vertexBuffers.emplace_back(newBuffer);

        return newBuffer;
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::LoadTextureData(
        const ResourceManagement::TextureMetadata& metadata,
        GraphicsTextureAddressMode addressMode,
        GraphicsTextureKind textureKind)
    {
        auto currentContext = _graphicsDevice->GetCurrentContext();

        std::shared_ptr<GraphicsTexture> texture2d =
            _graphicsDevice->GetMemoryAllocator()->CreateTextureWithDefaultArguments(
                addressMode, textureKind, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, metadata.width,
                metadata.height);

        std::shared_ptr<GraphicsBuffer> stagingBuffer =
            GetStagingBufferWithProperSizeHandling(texture2d->GetSize(), currentContext);

        auto texture2dRegion = texture2d->Allocate(texture2d->GetSize(), 4);
        auto pTextureData = stagingBuffer->Map<uint8_t>(texture2dRegion);
        memcpy_s(pTextureData, metadata.data.size(), metadata.data.data(), metadata.data.size());
        stagingBuffer->UnmapAndWrite(texture2dRegion);

        currentContext->Copy(texture2d, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        _textures.emplace_back(texture2d);
        currentContext->BeginFrame();

        return texture2dRegion;
    }
}
