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
    public:
        virtual ~GraphicsDeviceObject() noexcept = default;

        [[nodiscard]] std::weak_ptr<GraphicsDevice<TBackend>> GetDevice() const;
    };
}
