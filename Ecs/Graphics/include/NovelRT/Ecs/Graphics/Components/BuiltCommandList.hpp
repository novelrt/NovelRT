#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsProvider.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>

#include <memory>

namespace NovelRT::Ecs::Graphics::Components
{
    template <typename TGraphicsBackend>
    struct BuiltCommandList
    {
        std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>* commandList;
    };
}
