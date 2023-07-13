#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstdint>
#include <memory>


namespace NovelRT::Graphics
{
    class GraphicsAdapter;
    class GraphicsDevice;
    class GraphicsProvider;
    class GraphicsBuffer;
    class GraphicsTexture;

    class GraphicsMemoryAllocator
    {
    private:
        std::shared_ptr<GraphicsProvider> _provider;
        std::shared_ptr<GraphicsAdapter> _adapter;
        std::shared_ptr<GraphicsDevice> _device;

    public:
        GraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                std::shared_ptr<GraphicsAdapter> adapter,
                                std::shared_ptr<GraphicsDevice> device);

        [[nodiscard]] std::shared_ptr<GraphicsProvider> GetProvider() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsAdapter> GetAdapter() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsDevice> GetDevice() const noexcept;
        [[nodiscard]] virtual std::shared_ptr<GraphicsBuffer> CreateBuffer(size_t size) = 0; // TODO: these two methods probably need more args?
        [[nodiscard]] virtual std::shared_ptr<GraphicsTexture> CreateTexture(size_t size) = 0;
    };
}