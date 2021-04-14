// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IGRAPHICSSURFACE_H
#define NOVELRT_IGRAPHICSSURFACE_H

#include <optional>
#include "../../Maths/GeoVector2F.h"
#include "../../Utilities/Event.h"
#include "GraphicsSurfaceKind.h"

namespace NovelRT::Experimental::Graphics
{
    class IGraphicsSurface
    {
    public:
        std::optional<Utilities::Event<Maths::GeoVector2F>> SizeChanged;

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

#endif // NOVELRT_IGRAPHICSSURFACE_H