#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>
#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsRenderPass : public GraphicsDeviceObject<TBackend>
    {
    public:
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<GraphicsRenderPass<TBackend>> shared_from_this();
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        std::shared_ptr<const GraphicsRenderPass<TBackend>> shared_from_this() const;

        explicit GraphicsRenderPass() = delete;
    };
}
