#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsRenderPass;

    template<typename TBackend>
    struct SecondaryCmdListInfo
    {
        std::shared_ptr<GraphicsRenderPass<TBackend>> renderPass = nullptr;
        size_t subpassIndex = 0;
    };
}
