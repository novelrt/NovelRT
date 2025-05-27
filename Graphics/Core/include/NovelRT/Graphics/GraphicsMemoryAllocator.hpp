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
    template<typename TBackend> class GraphicsDeviceObject;
    template<typename TBackend> class GraphicsProvider;
    template<typename TBackend> class GraphicsBuffer;
    template<typename TBackend> class GraphicsTexture;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsMemoryAllocator : public GraphicsDeviceObject<TBackend>
    {
    public:
        //NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsMemoryAllocator<TBackend>> shared_from_this();

        GraphicsMemoryAllocator() = delete;
        ~GraphicsMemoryAllocator();

        [[nodiscard]] std::shared_ptr<GraphicsProvider<TBackend>> GetProvider() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer<TBackend>> CreateBuffer(const GraphicsBufferCreateInfo& createInfo);
        [[nodiscard]] std::shared_ptr<GraphicsBuffer<TBackend>> CreateBuffer(GraphicsBufferKind bufferKind,
                                                                             GraphicsResourceAccess cpuAccessKind,
                                                                             GraphicsResourceAccess gpuAccessKind,
                                                                             size_t size);

        [[nodiscard]] std::shared_ptr<GraphicsTexture<TBackend>> CreateTexture(
            const GraphicsTextureCreateInfo& createInfo);

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
