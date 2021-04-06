// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_QUEUEFAMILYINDICES_H
#define NOVELRT_QUEUEFAMILYINDICES_H

#include <optional>

namespace NovelRT::Experimental::Graphics::Vulkan
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        [[nodiscard]] inline bool IsComplete() const noexcept
        {
            return graphicsFamily.has_value();
        }
    };
}

#endif // NOVELRT_QUEUEFAMILYINDICES_H
