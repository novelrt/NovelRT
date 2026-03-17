#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/NullPointerException.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsDevice;
    template<typename TBackend>
    class GraphicsProvider;
    template<typename TBackend>
    class GraphicsSurfaceContext;

    template<typename TBackend>
    struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsAdapter : public std::enable_shared_from_this<GraphicsAdapter<TBackend>>
    {
    public:
        GraphicsAdapter() = delete;
        ~GraphicsAdapter() noexcept = default;

        [[nodiscard]] uint32_t GetDeviceId() const;
        [[nodiscard]] const std::string& GetName() const;
        [[nodiscard]] GraphicsProvider<TBackend>* GetProvider() const;
        [[nodiscard]] uint32_t GetVendorId() const;

        [[nodiscard]] std::shared_ptr<GraphicsDevice<TBackend>> CreateDevice(
            const std::shared_ptr<GraphicsSurfaceContext<TBackend>>& surfaceContext);
    };
}
