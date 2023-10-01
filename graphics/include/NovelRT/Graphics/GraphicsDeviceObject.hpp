#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <stdexcept>

namespace NovelRT::Graphics
{
    class GraphicsDeviceObject : public std::enable_shared_from_this<GraphicsDeviceObject>
    {
    private:
        std::weak_ptr<GraphicsDevice> _graphicsDevice;

    public:
        explicit GraphicsDeviceObject(std::shared_ptr<GraphicsDevice> graphicsDevice) noexcept
            : _graphicsDevice(graphicsDevice)
        {
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsDevice> GetDevice() const
        {
            if (_graphicsDevice.expired())
            {
                throw std::runtime_error("The graphics device has expired!");
            }

            return _graphicsDevice.lock();
        }

        virtual ~GraphicsDeviceObject() noexcept = default;
    };
}
