#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsBufferKind.hpp>
#include <NovelRT/Graphics/GraphicsResourceAccess.hpp>
#include <cstdint>
#include <memory>

namespace NovelRT::Graphics
{
    class GraphicsAdapter;
    class GraphicsDevice;
    class GraphicsProvider;
    class GraphicsBuffer;
    struct GraphicsBufferCreateInfo;
    class GraphicsTexture;
    struct GraphicsTextureCreateInfo;

    class GraphicsMemoryAllocator : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsProvider> _provider;

    public:
        GraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider, std::shared_ptr<GraphicsDevice> device);

        [[nodiscard]] std::shared_ptr<GraphicsProvider> GetProvider() const noexcept;

        [[nodiscard]] virtual std::shared_ptr<GraphicsBuffer> CreateBuffer(
            const GraphicsBufferCreateInfo& createInfo) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateBuffer(GraphicsBufferKind bufferKind,
                                                                   GraphicsResourceAccess cpuAccessKind,
                                                                   GraphicsResourceAccess gpuAccessKind,
                                                                   size_t size);

        [[nodiscard]] virtual std::shared_ptr<GraphicsTexture> CreateTexture(
            const GraphicsTextureCreateInfo& createInfo) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTexture2DRepeatGpuWriteOnly(uint32_t width,
                                                                                         uint32_t height = 1);
    };
}