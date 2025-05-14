#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryRegionAllocationFlags.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <NovelRT/Graphics/GraphicsBufferCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsTextureAddressMode.hpp>
#include <NovelRT/Graphics/GraphicsTextureCreateInfo.hpp>
#include <NovelRT/Graphics/GraphicsTextureKind.hpp>
#include <NovelRT/Graphics/TexelFormat.hpp>
#include <cstdint>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;
    template<typename TBackend> class GraphicsDevice;
    template<typename TBackend> class GraphicsProvider;
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsTexture;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsMemoryAllocator : public GraphicsDeviceObject<TBackend>, public std::enable_shared_from_this<GraphicsMemoryAllocator<TBackend>>
    {
    public:
        using BackendMemoryAllocatorType = typename GraphicsBackendTraits<TBackend>::MemoryAllocatorType;

    private:
        std::shared_ptr<BackendMemoryAllocatorType> _implementation;
        std::shared_ptr<GraphicsProvider<TBackend>> _provider;

    public:
    using std::enable_shared_from_this<GraphicsMemoryAllocator<TBackend>>::shared_from_this;

        GraphicsMemoryAllocator(std::shared_ptr<BackendMemoryAllocatorType> implementation,
                                std::shared_ptr<GraphicsDevice<TBackend>> device,
                                std::shared_ptr<GraphicsProvider<TBackend>> provider)
            : GraphicsDeviceObject<TBackend>(device), _implementation(implementation), _provider(provider)
        {
        }

        [[nodiscard]] std::shared_ptr<GraphicsProvider<TBackend>> GetProvider() const noexcept
        {
            return _provider;
        }

        [[nodiscard]] std::shared_ptr<GraphicsBuffer<TBackend>> CreateBuffer(const GraphicsBufferCreateInfo& createInfo)
        {
            return std::make_shared<GraphicsBuffer<TBackend>>(
                _implementation->CreateBuffer(createInfo),
                this->shared_from_this(),
                createInfo);
        }

        [[nodiscard]] std::shared_ptr<GraphicsBuffer<TBackend>> CreateBuffer(GraphicsBufferKind bufferKind,
                                                                             GraphicsResourceAccess cpuAccessKind,
                                                                             GraphicsResourceAccess gpuAccessKind,
                                                                             size_t size)
        {
            return CreateBuffer(GraphicsBufferCreateInfo{bufferKind, cpuAccessKind, gpuAccessKind, size,
                                                         GraphicsMemoryRegionAllocationFlags::None});
        }

        [[nodiscard]] std::shared_ptr<GraphicsTexture<TBackend>> CreateTexture(
            const GraphicsTextureCreateInfo& createInfo)
        {
            return std::make_shared<GraphicsTexture<TBackend>>(
                _implementation->CreateTexture(createInfo),
                this->shared_from_this(),
                createInfo);
        }

        [[nodiscard]] std::shared_ptr<GraphicsTexture<TBackend>> CreateTexture2DRepeatGpuWriteOnly(uint32_t width,
                                                                                                   uint32_t height = 1)
        {
            return CreateTexture(
                GraphicsTextureCreateInfo{GraphicsTextureAddressMode::Repeat, GraphicsTextureKind::TwoDimensional,
                                          GraphicsResourceAccess::None, GraphicsResourceAccess::Write, width, height, 1,
                                          GraphicsMemoryRegionAllocationFlags::None, TexelFormat::R8G8B8A8_UNORM});
        }
    };
}
