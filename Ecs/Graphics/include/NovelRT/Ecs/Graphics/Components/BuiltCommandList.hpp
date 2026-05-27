#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsCmdList.hpp>
#include <NovelRT/Graphics/GraphicsProvider.hpp>

#include <memory>

namespace NovelRT::Ecs::Graphics::Components
{
    template<typename TGraphicsBackend>
    struct BuiltCommandList
    {
        std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>* commandList;

        inline BuiltCommandList& operator+=(const BuiltCommandList& other)
        {
            if (commandList != nullptr)
            {
                delete commandList;
            }

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const BuiltCommandList& other) const noexcept
        {
            return commandList == other.commandList;
        }

        [[nodiscard]] inline bool operator!=(const BuiltCommandList& other) const noexcept
        {
            return !(*this == other);
        }
    };
}
