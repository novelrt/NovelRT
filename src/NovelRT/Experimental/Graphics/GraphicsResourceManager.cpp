// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsResourceManager::GraphicsResourceManager(std::shared_ptr<GraphicsDevice> graphicsDevice,
                                                     size_t startingSize)
        : _graphicsDevice(std::move(graphicsDevice)),
          _stagingBuffer([&]() { return CreateStagingBuffer(); }), _stagingBufferSize(startingSize)
    {
    }

    GraphicsMemoryRegion<GraphicsResource> GraphicsResourceManager::LoadVertexDataUntyped(void* data,
                                                                                          size_t dataTypeSize,
                                                                                          size_t dataLength,
                                                                                          size_t alignment)
    {
        auto currentContext = _graphicsDevice->GetCurrentContext();
        std::shared_ptr<GraphicsBuffer> stagingBuffer = _stagingBuffer.getActual();

        size_t sizeToStage = dataTypeSize * dataLength;

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

        std::shared_ptr<GraphicsBuffer> vertexBuffer = GetOrCreateGraphicsBufferForAllocationSize(sizeToStage);
        auto vertexRegion = vertexBuffer->Allocate(sizeToStage, alignment);
        uint8_t* writeArea = stagingBuffer->Map<uint8_t>(vertexRegion);
        memcpy_s(writeArea, sizeToStage, data, sizeToStage);
        stagingBuffer->UnmapAndWrite(vertexRegion);
        currentContext->Copy(vertexBuffer, stagingBuffer);

        currentContext->EndFrame();
        _graphicsDevice->Signal(currentContext->GetFence());
        _graphicsDevice->WaitForIdle();
        currentContext->BeginFrame();

        return vertexRegion;
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

        //TODO: This needs to be improved.
        auto newBuffer = _graphicsDevice->GetMemoryAllocator()->CreateBufferWithDefaultArguments(
            GraphicsBufferKind::Vertex, GraphicsResourceAccess::None, GraphicsResourceAccess::Write, allocationSize);

        _vertexBuffers.emplace_back(newBuffer);

        return newBuffer;
    }

    GraphicsResourceManager::GraphicsResourceManager(const GraphicsResourceManager& other) :
          _graphicsDevice(nullptr),
          _stagingBuffer(nullptr), _stagingBufferSize(0)
    {
        *this = other;
    }

    GraphicsResourceManager::GraphicsResourceManager(GraphicsResourceManager&& other) noexcept :
          _graphicsDevice(nullptr),
          _stagingBuffer(nullptr), _stagingBufferSize(0)
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

        _stagingBufferSize = std::move(other._stagingBufferSize);
        return *this;
    }
}
