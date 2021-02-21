// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H

#include "GraphicsResourceCpuAccessKind.h"
#include <cstdint>

namespace NovelRT::Experimental::Graphics
{
    //TODO: Rename these to something that indicates high level later!
    class GraphicsResource
    {
    private:
        GraphicsResourceCpuAccessKind _enabledAccessMode;

    public:
        explicit GraphicsResource(GraphicsResourceCpuAccessKind enabledAccessMode) noexcept
            : _enabledAccessMode(enabledAccessMode)
        {
        }

        [[nodiscard]] inline GraphicsResourceCpuAccessKind EnabledAccessMode() const noexcept
        {
            return _enabledAccessMode;
        }

        virtual std::byte* MapUntyped(GraphicsResourceCpuAccessKind accessMode) = 0;
        virtual std::byte* MapRangeUntyped(GraphicsResourceCpuAccessKind accessMode, size_t range) = 0;

        template<typename T> T* Map(GraphicsResourceCpuAccessKind accessMode)
        {
            return reinterpret_cast<T*>(MapUntyped(accessMode));
        }

        template<typename T> T* MapRange(GraphicsResourceCpuAccessKind accessMode, size_t range)
        {
            return reinterpret_cast<T*>(MapRangeUntyped(accessMode, range));
        }

        virtual void Unmap() = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSRESOURCE_H
