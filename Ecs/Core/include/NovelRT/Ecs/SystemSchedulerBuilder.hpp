#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SystemScheduler.hpp>

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <optional>
#include <vector>

namespace NovelRT::Ecs
{
    /**
     * @brief A convenience type to help with the creation of an ECS instance.
     */
    class SystemSchedulerBuilder
    {
    private:
        std::optional<uint32_t> _threadCount;
        std::vector<std::function<void(SystemScheduler&)>> _configureCallbacks;

    public:
        /**
         * @brief Defines how many worker threads should be configured for this ECS instance.
         *
         * @param threadCount The amount of threads.
         * @returns A reference to this to allow method chaining.
         */
        SystemSchedulerBuilder& WithThreadCount(uint32_t threadCount) noexcept
        {
            _threadCount = threadCount;
            return *this;
        }

        /**
         * @brief Adds a callback to configure the system scheduler after it has been created.
         *
         * @param configure The callback to use to configure the scheduler.
         * @returns A reference to this to allow method chaining.
         */
        SystemSchedulerBuilder& Configure(std::function<void(SystemScheduler&)> configure) noexcept
        {
            _configureCallbacks.emplace_back(configure);
            return *this;
        }


        /**
         * @brief Creates the ECS instance and registers component types to it.
         * This is the final method you should call to obtain the ECS instance.
         *
         * @returns An instance of the ECS SystemScheduler based on the provided configuration.
         */
        [[nodiscard]] SystemScheduler Build()
        {
            SystemScheduler scheduler(_threadCount.value_or(0));

            for (auto&& configure : _configureCallbacks)
            {
                configure(scheduler);
            }

            scheduler.SpinThreads();

            return scheduler;
        }
    };
}
