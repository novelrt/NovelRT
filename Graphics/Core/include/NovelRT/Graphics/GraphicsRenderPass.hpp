#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/GraphicsDevice.hpp"
#include <memory>

namespace NovelRT::Graphics
{
    template <typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend> class GraphicsRenderPass : std::enable_shared_from_this<GraphicsRenderPass<TBackend>>
    {
    public:
        using BackendRenderPassType = typename GraphicsBackendTraits<TBackend>::RenderPassType;

    private:
        std::unique_ptr<BackendRenderPassType> _implementation;

    public:
        explicit GraphicsRenderPass(std::unique_ptr<BackendRenderPassType> implementation)
            : _implementation(std::move(implementation))
        {
        }

        [[nodiscard]] BackendRenderPassType* GetImplementation() const noexcept
        {
            return _implementation.get();
        }
    };
}
