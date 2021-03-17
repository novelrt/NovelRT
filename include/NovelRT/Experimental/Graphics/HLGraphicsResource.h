// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_HLGRAPHICSRESOURCE_H
#define NOVELRT_EXPERIMENTAL_HLGRAPHICSRESOURCE_H

#include "GraphicsResourceCpuAccessKind.h"
#include "LLGraphicsResource.h"
#include "LLGraphicsResourceViewContainer.h"
#include <cstdint>
#include <gsl/span>
#include <memory>

namespace NovelRT::Experimental::Graphics
{
    class HLGraphicsResource
    {
    private:
        GraphicsResourceCpuAccessKind _enabledAccessMode;


    public:
        explicit HLGraphicsResource(GraphicsResourceCpuAccessKind enabledAccessMode) noexcept
            : _enabledAccessMode(enabledAccessMode)
        {
        }

        [[nodiscard]] virtual gsl::span<std::byte> MapUntyped(GraphicsResourceCpuAccessKind accessMode) = 0;
        [[nodiscard]] virtual gsl::span<std::byte> MapRangeUntyped(GraphicsResourceCpuAccessKind accessMode,
                                                                   size_t offset,
                                                                   size_t range) = 0;
        [[nodiscard]] virtual std::shared_ptr<LLGraphicsResource> GetLLResourceUntyped() const = 0;

        [[nodiscard]] inline GraphicsResourceCpuAccessKind GetEnabledAccessMode() const noexcept
        {
            return _enabledAccessMode;
        }

        template<typename T> [[nodiscard]] gsl::span<T> Map(GraphicsResourceCpuAccessKind accessMode)
        {
            return gsl::span<T>(MapUntyped(accessMode));
        }

        template<typename T> [[nodiscard]] gsl::span<T> MapRange(GraphicsResourceCpuAccessKind accessMode, size_t offset, size_t range)
        {
            return gsl::span<T>(MapRangeUntyped(accessMode, offset, range));
        }

        template<typename T> [[nodiscard]] LLGraphicsResourceViewContainer<T> GetLLResource() const
        {
            return LLGraphicsResourceViewContainer<T>(GetLLResourceUntyped());
        }

        virtual void Unmap() = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_HLGRAPHICSRESOURCE_H
