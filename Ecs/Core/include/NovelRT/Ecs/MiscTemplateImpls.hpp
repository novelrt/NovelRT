#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/SystemScheduler.hpp>

namespace NovelRT::Ecs
{
    template<typename TWork, typename TCompletion>
    requires Detail::ValidScheduleWithCompletion<TWork, TCompletion> void Catalogue::ScheduleWithCompletion(
        TWork&& work,
        TCompletion&& completion) noexcept
    {
        _scheduler.ScheduleWithCompletion(std::forward<TWork>(work), std::forward<TCompletion>(completion));
    }

    template<typename TWork, typename TCompletion>
    requires Detail::ValidScheduleWithCompletion<TWork, TCompletion> void SystemScheduler::ScheduleWithCompletion(
        TWork&& work,
        TCompletion&& completion) noexcept
    {
        _asyncArena->execute(
            [&]()
            {
                _asyncTasks->run(
                    [work = std::forward<TWork>(work), completion = std::forward<TCompletion>(completion),
                     this]() mutable
                    {
                        auto result = work();
                        _pendingCompletions.push([completion = std::move(completion), result = std::move(result)](
                                                     Timing::Timestamp delta, Catalogue cat) mutable
                                                 { completion(delta, cat, std::move(result)); });
                    });
            });
    }
}