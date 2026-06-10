#pragma once

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/UI/UIComponentType.hpp>

#include <limits>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT::Ecs::UI::Components
{
    struct UIElement
    {
        private:

        public:
            EntityId entity = std::numeric_limits<EntityId>::max();
            NovelRT::Ecs::UI::UIComponentType Type = NovelRT::Ecs::UI::UIComponentType::Text;
            
            inline UIElement& operator+=(const UIElement& other)
            {
                *this = other;
                return *this;
            }

            [[nodiscard]] inline bool operator==(const UIElement& other) const noexcept
            {
                return Type == other.Type;
            }

            [[nodiscard]] inline bool operator!=(const UIElement& other) const noexcept
            {
                return !(*this == other);
            }
    };
}