#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/Exceptions.h>
#include <memory>
#include <stdexcept>
#include <string>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsDevice;
    template<typename TBackend> class GraphicsProvider;
    template<typename TBackend> class GraphicsSurfaceContext;

    template<typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsAdapter : public std::enable_shared_from_this<GraphicsAdapter<TBackend>>
    {
    public:
        using BackendAdapterType = typename GraphicsBackendTraits<TBackend>::AdapterType;

    private:
        std::shared_ptr<BackendAdapterType> _implementation;
        std::shared_ptr<GraphicsProvider<TBackend>> _provider;

    public:
        GraphicsAdapter(std::shared_ptr<BackendAdapterType> implementation,
                        std::shared_ptr<GraphicsProvider<TBackend>> provider)
            : _implementation(implementation), _provider(provider)
        {
            if (!_provider)
            {
                throw Exceptions::NullPointerException(
                    "The provided GraphicsProvider pointer is nullptr or an invalid pointer.");
            }
        }

        ~GraphicsAdapter() noexcept = default;

        [[nodiscard]] uint32_t GetDeviceId()
        {
            return _implementation->GetDeviceId();
        }

        [[nodiscard]] const std::string& GetName()
        {
            return _implementation->GetName();
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsProvider<TBackend>> GetProvider() const
        {
            return _provider;
        }

        [[nodiscard]] uint32_t GetVendorId()
        {
            return _implementation->GetVendorId();
        }

        [[nodiscard]] std::shared_ptr<GraphicsDevice<TBackend>> CreateDevice(
            std::shared_ptr<GraphicsSurfaceContext<TBackend>> surfaceContext,
            int32_t contextCount)
        {
            return std::make_shared<GraphicsDevice<TBackend>>(
                _implementation->CreateDevice(surfaceContext->GetImplementation(), contextCount),
                this->shared_from_this(),
                surfaceContext);
        }
    };
}
