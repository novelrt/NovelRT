#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>
#include <stdexcept>
#include <string>
#include <NovelRT/Exceptions/Exceptions.h>

namespace NovelRT::Graphics
{
    class GraphicsDevice;
    class GraphicsProvider;
    class GraphicsSurfaceContext;

    class GraphicsAdapter : public std::enable_shared_from_this<GraphicsAdapter>
    {
    private:
        std::weak_ptr<GraphicsProvider> _provider;

    public:
        explicit GraphicsAdapter(std::weak_ptr<GraphicsProvider> provider) : _provider(std::move(provider))
        {
            if (_provider.expired())
            {
                throw Exceptions::NullPointerException(
                    "The provided GraphicsProvider pointer is nullptr or an invalid pointer.");
            }
        }

        [[nodiscard]] virtual uint32_t GetDeviceId() = 0;

        [[nodiscard]] virtual const std::string& GetName() = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsProvider> GetProvider() const
        {
            if (_provider.expired())
            {
                throw std::runtime_error("Provider has expired.");
            }

            return _provider.lock();
        }

        [[nodiscard]] virtual uint32_t GetVendorId() = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsDevice> CreateDevice(
            std::shared_ptr<GraphicsSurfaceContext> surfaceContext,
            int32_t contextCount) = 0;

        virtual ~GraphicsAdapter() = default;
    };
}
