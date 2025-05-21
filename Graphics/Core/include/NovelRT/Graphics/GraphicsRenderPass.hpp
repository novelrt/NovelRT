#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include "NovelRT/Graphics/GraphicsDevice.hpp"
#include <memory>

namespace NovelRT::Graphics
{
    template <typename TBackend> struct GraphicsBackendTraits;

    template<typename TBackend>
    class GraphicsRenderPass : public std::enable_shared_from_this<GraphicsRenderPass<TBackend>>
    {
    public:
        explicit GraphicsRenderPass() = delete;
    };
}
