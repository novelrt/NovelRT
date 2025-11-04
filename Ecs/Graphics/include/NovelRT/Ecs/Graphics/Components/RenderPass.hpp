#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Utilities/Atom.hpp>

namespace NovelRT::Ecs::Graphics::Components
{
    using RenderPassId = NovelRT::Atom;

    struct RenderPass
    {
        RenderPassId renderPassIndex;
    };
}
