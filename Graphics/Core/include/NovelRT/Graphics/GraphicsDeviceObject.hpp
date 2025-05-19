#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <stdexcept>

namespace NovelRT::Graphics
{
    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsDeviceObject : public std::enable_shared_from_this<GraphicsDeviceObject<TBackend>>
    {
    private:
        std::weak_ptr<GraphicsDevice<TBackend>> _graphicsDevice;

    public:
        explicit GraphicsDeviceObject(std::weak_ptr<GraphicsDevice<TBackend>> graphicsDevice) noexcept
            : _graphicsDevice(std::move(graphicsDevice))
        {
        }

        virtual ~GraphicsDeviceObject() noexcept = default;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<TBackend>> GetDevice() const
        {
            return _graphicsDevice.lock();
        }
    };
}
