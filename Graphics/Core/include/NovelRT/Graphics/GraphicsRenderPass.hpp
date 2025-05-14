#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsRenderPass
    {
    public:
        using BackendRenderPassType = typename GraphicsBackendTraits<TBackend>::RenderPassType;

    private:
        std::shared_ptr<BackendRenderPassType> _implementation;

    public:
        explicit GraphicsRenderPass(std::shared_ptr<BackendRenderPassType> implementation)
            : _implementation(implementation)
        {
        }

        [[nodiscard]] std::shared_ptr<BackendRenderPassType> GetImplementation() const noexcept
        {
            return _implementation;
        }
    };
}