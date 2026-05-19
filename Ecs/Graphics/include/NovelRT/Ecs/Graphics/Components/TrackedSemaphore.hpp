#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsSemaphore.hpp>

#include <memory>

namespace NovelRT::Ecs::Graphics::Components
{
    template<typename TGraphicsBackend>
    struct TrackedSemaphore
    {
        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>* semaphore = nullptr;
        uint64_t signalValue = 0;
        bool isWaitSemaphore = true;

        inline TrackedSemaphore& operator+=(const TrackedSemaphore& other)
        {
            if (semaphore != nullptr)
            {
                delete semaphore;
            }
            

            *this = other;
            return *this;
        }

        [[nodiscard]] inline bool operator==(const TrackedSemaphore& other) const noexcept
        {
            return semaphore == other.semaphore && signalValue == other.signalValue;
        }

        [[nodiscard]] inline bool operator!=(const TrackedSemaphore& other) const noexcept
        {
            return !(*this == other);
        }
    };
}