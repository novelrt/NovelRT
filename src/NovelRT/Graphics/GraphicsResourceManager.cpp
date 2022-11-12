// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/Graphics.h"
#include "NovelRT/Graphics/GraphicsResourceManager.h"

namespace NovelRT::Graphics
{
    GraphicsResourceManager::GraphicsResourceManager(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                                     size_t startingStagingBufferSize)
        : _stagingBuffer([&]() { return CreateStagingBuffer(); }),
          _graphicsDevice(std::move(graphicsDevice)),
          _stagingBufferSize(startingStagingBufferSize)
    {
        if (_stagingBufferSize == 0)
        {
            _stagingBufferSize = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;
        }
    }

    GraphicsResourceManager::GraphicsResourceManager(const GraphicsResourceManager& other)
        : _stagingBuffer(nullptr), _defaultBuffers{}, _vertexBuffers{}, _indexBuffers{}, _constantBuffers{}, _textures{}, _graphicsDevice(nullptr), _stagingBufferSize(0)
    {
        *this = other;
    }

    GraphicsResourceManager::GraphicsResourceManager(GraphicsResourceManager&& other) noexcept
        : _stagingBuffer(nullptr), _defaultBuffers{}, _vertexBuffers{}, _indexBuffers{}, _constantBuffers{}, _textures{}, _graphicsDevice(nullptr), _stagingBufferSize(0)
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
        _defaultBuffers = {};
        _vertexBuffers = {};
        _indexBuffers = {};
        _constantBuffers = {};
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

        _defaultBuffers = std::move(other._defaultBuffers);
        _vertexBuffers = std::move(other._vertexBuffers);
        _indexBuffers = std::move(other._indexBuffers);
        _constantBuffers = std::move(other._constantBuffers);
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

        std::shared_ptr<GraphicsBuffer> vertexBuffer = GetOrCreateGraphicsBufferForAllocationSize(sizeToStage, GraphicsBufferKind::Vertex);
        auto vertexRegion = vertexBuffer->Allocate(sizeToStage, alignment);
        auto writeArea = stagingBuffer->Map<uint8_t>(vertexRegion);
#ifdef WIN32
        memcpy_s(writeArea, sizeToStage, data, sizeToStage);
#else
        memcpy(writeArea, data, sizeToStage);
#endif
        stagingBuffer->UnmapAndWrite(vertexRegion);
        currentContext->Copy(vertexBuffer, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        currentContext->BeginFrame();

        return vertexRegion;
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::LoadIndexDataUntyped(void* data,
                                                                                         size_t dataTypeSize,
                                                                                         size_t dataLength,
                                                                                         size_t alignment)
    {
        size_t sizeToStage = dataTypeSize * dataLength;
        auto currentContext = _graphicsDevice->GetCurrentContext();

        std::shared_ptr<GraphicsBuffer> stagingBuffer =
            GetStagingBufferWithProperSizeHandling(sizeToStage, currentContext);

        std::shared_ptr<GraphicsBuffer> indexBuffer = GetOrCreateGraphicsBufferForAllocationSize(sizeToStage, GraphicsBufferKind::Index);
        auto indexRegion = indexBuffer->Allocate(sizeToStage, alignment);
        auto writeArea = stagingBuffer->Map<uint8_t>(indexRegion);
#ifdef WIN32
        memcpy_s(writeArea, sizeToStage, data, sizeToStage);
#else
        memcpy(writeArea, data, sizeToStage);
#endif
        stagingBuffer->UnmapAndWrite(indexRegion);
        currentContext->Copy(indexBuffer, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        currentContext->BeginFrame();

        return indexRegion;
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
            Graphics::GraphicsBufferKind::Default, Graphics::GraphicsResourceAccess::Write,
            Graphics::GraphicsResourceAccess::Read, _stagingBufferSize);
    }

    std::shared_ptr<GraphicsBuffer> GraphicsResourceManager::GetOrCreateGraphicsBufferForAllocationSize(
        size_t allocationSize, GraphicsBufferKind bufferKind)
    {
        std::vector<std::shared_ptr<GraphicsBuffer>>* buffers = nullptr;

        switch (bufferKind)
        {
            case GraphicsBufferKind::Default:
                buffers = &_defaultBuffers;
                break;
            case GraphicsBufferKind::Vertex:
                buffers = &_vertexBuffers;
                break;
            case GraphicsBufferKind::Index:
                buffers = &_indexBuffers;
                break;
            case GraphicsBufferKind::Constant:
                buffers = &_constantBuffers;
                break;
        }

        for (auto&& buffer : *buffers)
        {
            if (buffer->GetLargestFreeRegionSize() >= allocationSize)
            {
                return buffer;
            }
        }

        std::shared_ptr<GraphicsBuffer> newBuffer = nullptr;

        if (bufferKind == GraphicsBufferKind::Constant)
        {
            newBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
                GraphicsBufferKind::Constant, GraphicsResourceAccess::Write, GraphicsResourceAccess::Read,
                ((allocationSize > _tenMegabytesAsBytes) ? allocationSize : _tenMegabytesAsBytes));
        }
        else
        {
            size_t minimumBlockSize = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;
            size_t sizeToAllocate = _graphicsDevice->GetMemoryAllocator()->GetSettings().MinimumBlockSize;
            while (sizeToAllocate < allocationSize)
            {
                sizeToAllocate += minimumBlockSize;
            }

            newBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
                bufferKind, GraphicsResourceAccess::None, GraphicsResourceAccess::Write,
                ((allocationSize > _tenMegabytesAsBytes) ? allocationSize : _tenMegabytesAsBytes));
        }

        switch (bufferKind)
        {
            case GraphicsBufferKind::Default:
                _defaultBuffers.emplace_back(newBuffer);
                break;
            case GraphicsBufferKind::Vertex:
                _vertexBuffers.emplace_back(newBuffer);
                break;
            case GraphicsBufferKind::Index:
                _indexBuffers.emplace_back(newBuffer);
                break;
            case GraphicsBufferKind::Constant:
                _constantBuffers.emplace_back(newBuffer);
                break;
        }


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

#ifdef WIN32
        memcpy_s(pTextureData, metadata.data.size(), metadata.data.data(), metadata.data.size());
#else
        memcpy(pTextureData, metadata.data.data(), metadata.data.size());
#endif

        stagingBuffer->UnmapAndWrite(texture2dRegion);

        currentContext->Copy(texture2d, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        _textures.emplace_back(texture2d);
        currentContext->BeginFrame();

        return texture2dRegion;
    }

    void GraphicsResourceManager::FreeVertexData(GraphicsMemoryRegion<GraphicsResource>& vertexResource)
    {
        auto collection = vertexResource.GetCollection();
        auto bufferPtr = std::dynamic_pointer_cast<GraphicsBuffer>(collection);

        if (bufferPtr == nullptr)
        {
            throw Exceptions::InvalidOperationException("An invalid graphics resource was passed into FreeVertexData.");
        }

        collection->Free(vertexResource);

        if (bufferPtr->GetSize() == bufferPtr->GetLargestFreeRegionSize())
        {
            unused(std::remove(_vertexBuffers.begin(), _vertexBuffers.end(), bufferPtr));
        }
    }

    void GraphicsResourceManager::FreeIndexData(GraphicsMemoryRegion<GraphicsResource>& indexResource)
    {
        auto collection = indexResource.GetCollection();
        auto bufferPtr = std::dynamic_pointer_cast<GraphicsBuffer>(collection);

        if (bufferPtr == nullptr)
        {
            throw Exceptions::InvalidOperationException("An invalid graphics resource was passed into FreeIndexData.");
        }

        collection->Free(indexResource);

        if (bufferPtr->GetSize() == bufferPtr->GetLargestFreeRegionSize())
        {
            unused(std::remove(_indexBuffers.begin(), _indexBuffers.end(), bufferPtr));
        }
    }

    void GraphicsResourceManager::FreeTextureData(GraphicsMemoryRegion<GraphicsResource>& textureResource)
    {
        auto collection = textureResource.GetCollection();
        auto texturePtr = std::dynamic_pointer_cast<GraphicsTexture>(collection);

        if (texturePtr == nullptr)
        {
            throw Exceptions::InvalidOperationException(
                "An invalid graphics resource was passed into FreeTextureData.");
        }

        collection->Free(textureResource);

        // For now, a single region is a single texture pointer, so we can just remove it.
        unused(std::remove(_textures.begin(), _textures.end(), texturePtr));
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::LoadConstantBufferDataToNewRegion(void* data,
                                                                                                      size_t size,
                                                                                                      size_t alignment)
    {
        auto bufferPtr = GetOrCreateGraphicsBufferForAllocationSize(size, GraphicsBufferKind::Constant);
        auto allocation = bufferPtr->Allocate(size, alignment);
        uint8_t* destination = bufferPtr->Map<uint8_t>(allocation);

#ifdef WIN32
        memcpy_s(destination, size, data, size);
#else
        memcpy(destination, data, size);
#endif

        bufferPtr->UnmapAndWrite(allocation);
        return allocation;
    }

    void GraphicsResourceManager::LoadConstantBufferDataToExistingRegion(
        GraphicsMemoryRegion<GraphicsResource>& targetMemoryResource,
        void* data,
        size_t size)
    {
        auto bufferPtr = std::dynamic_pointer_cast<GraphicsBuffer>(targetMemoryResource.GetCollection());

        if (bufferPtr == nullptr)
        {
            throw Exceptions::InvalidOperationException("The provided region was not provided by a constant buffer");
        }

        if (std::find(_constantBuffers.begin(), _constantBuffers.end(), bufferPtr) == _constantBuffers.end())
        {
            throw Exceptions::InvalidOperationException(
                "The provided region is not managed by this instance of GraphicsResourceManager.");
        }

        if (targetMemoryResource.GetSize() < size)
        {
            throw std::out_of_range("The size of the data is too large for the specified memory region.");
        }

        uint8_t* destination = bufferPtr->Map<uint8_t>(targetMemoryResource);

#ifdef WIN32
        memcpy_s(destination, size, data, size);
#else
        memcpy(destination, data, size);
#endif

        bufferPtr->UnmapAndWrite(targetMemoryResource);
    }

    void GraphicsResourceManager::FreeConstantBufferData(GraphicsMemoryRegion<GraphicsResource>& region)
    {
        auto collection = region.GetCollection();
        auto bufferPtr = std::dynamic_pointer_cast<Graphics::GraphicsBuffer>(collection);

        if (bufferPtr == nullptr)
        {
            throw Exceptions::InvalidOperationException(
                "An invalid graphics resource was passed into FreeConstantBufferRegion");
        }

        auto iterator = std::find(_constantBuffers.begin(), _constantBuffers.end(), bufferPtr);

        if (iterator == _constantBuffers.end())
        {
            throw Exceptions::InvalidOperationException("The constant buffer this region belongs to is not managed by "
                                                        "this instance of GraphicsResourceManager.");
        }

        bufferPtr->Free(region);

        if (bufferPtr->GetSize() == bufferPtr->GetLargestFreeRegionSize())
        {
            _constantBuffers.erase(iterator);
        }
    }

    uint8_t* GraphicsResourceManager::MapConstantBufferRegionForWritingUntyped(
        GraphicsMemoryRegion<GraphicsResource>& targetMemoryResource)
    {
        auto bufferPtr = std::dynamic_pointer_cast<GraphicsBuffer>(targetMemoryResource.GetCollection());

        if (bufferPtr == nullptr)
        {
            throw Exceptions::InvalidOperationException(
                "An invalid graphics resource was passed into FreeConstantBufferRegion");
        }

        size_t oldLength = _constantBuffersToUnmapAndWrite.size();
        for (size_t i = 0; i < _constantBuffers.size(); i++)
        {
            if (bufferPtr != _constantBuffers[i])
            {
                continue;
            }

            _constantBuffersToUnmapAndWrite.emplace(i);
            break;
        }

        if (oldLength >= _constantBuffersToUnmapAndWrite.size())
        {
            throw Exceptions::InvalidOperationException("The constant buffer this region belongs to is not managed by "
                                                        "this instance of GraphicsResourceManager.");
        }

        return bufferPtr->Map<uint8_t>(targetMemoryResource);
    }

    void GraphicsResourceManager::UnmapAndWriteAllConstantBuffers() noexcept
    {
        for (size_t index : _constantBuffersToUnmapAndWrite)
        {
            _constantBuffers[index]->UnmapAndWrite();
        }

        _constantBuffersToUnmapAndWrite.clear();
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::AllocateConstantBufferRegion(size_t size,
                                                                                                 size_t alignment)
    {
        auto bufferPtr = GetOrCreateGraphicsBufferForAllocationSize(size, GraphicsBufferKind::Constant);
        return bufferPtr->Allocate(size, alignment);
    }
}
