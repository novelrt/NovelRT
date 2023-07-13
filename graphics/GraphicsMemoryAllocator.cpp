// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsMemoryAllocator.hpp>

namespace NovelRT::Graphics
{
    GraphicsMemoryAllocator::GraphicsMemoryAllocator(std::shared_ptr<GraphicsProvider> provider,
                                                     std::shared_ptr<GraphicsAdapter> adapter,
                                                     std::shared_ptr<GraphicsDevice> device)
        : _provider(provider), _adapter(_adapter), _device(device)
    {
    }

    std::shared_ptr<GraphicsProvider> GraphicsMemoryAllocator::GetProvider() const noexcept
    {
        return _provider;
    }

    std::shared_ptr<GraphicsAdapter> GraphicsMemoryAllocator::GetAdapter() const noexcept
    {
        return _adapter;
    }

    std::shared_ptr<GraphicsDevice> GraphicsMemoryAllocator::GetDevice() const noexcept
    {
        return _device;
    }
}

