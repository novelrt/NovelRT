#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSurfaceKind.hpp>
#include <NovelRT/Maths/Maths.h>
#include <NovelRT/Utilities/Event.h>

namespace NovelRT::Graphics
{
    class IGraphicsSurface
    {
    public:
        Utilities::Event<Maths::GeoVector2F> SizeChanged;

        [[nodiscard]] virtual Maths::GeoVector2F GetSize() const noexcept = 0;

        [[nodiscard]] inline float GetWidth() const noexcept
        {
            return GetSize().x;
        }

        [[nodiscard]] inline float GetHeight() const noexcept
        {
            return GetSize().y;
        }

        [[nodiscard]] virtual void* GetHandle() const noexcept = 0;
        [[nodiscard]] virtual void* GetContextHandle() const noexcept = 0;
        [[nodiscard]] virtual GraphicsSurfaceKind GetKind() const noexcept = 0;
    };
}
