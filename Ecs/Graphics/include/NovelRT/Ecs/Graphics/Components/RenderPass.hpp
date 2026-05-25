#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDescriptorSet.hpp>

#include <NovelRT/Utilities/Atom.hpp>

namespace NovelRT::Ecs::Graphics::Components
{
    using RenderPassId = NovelRT::Atom;

    template<typename TGraphicsBackend>
    struct RenderPass
    {
        RenderPassId renderPassIndex;
        std::shared_ptr<NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>* descriptorSets;
        size_t descriptorSetCount = 0;

        inline RenderPass& operator+=(const RenderPass& other)
        {
            if (descriptorSets != nullptr)
            {
                delete[] descriptorSets;
            }

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const RenderPass& other) const noexcept
        {
            return renderPassIndex == other.renderPassIndex && descriptorSets == other.descriptorSets &&
                   descriptorSetCount == other.descriptorSetCount;
        }

        [[nodiscard]] inline bool operator!=(const RenderPass& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
