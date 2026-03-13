#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>

#include <NovelRT/Utilities/Atom.hpp>

namespace NovelRT::Ecs::Graphics::Components
{
    using RenderPassId = NovelRT::Atom;

    template <typename TGraphicsBackend>
    struct RenderPass
    {
        std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>* descriptorSet;
        RenderPassId renderPassIndex;

        inline RenderPass& operator+=(const RenderPass& other)
        {
            if (descriptorSet != nullptr) delete descriptorSet;
            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const RenderPass& other) const noexcept
        {
            return renderPassIndex == other.renderPassIndex
                && descriptorSet == other.descriptorSet;
        }

        [[nodiscard]] inline bool operator!=(const RenderPass& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
