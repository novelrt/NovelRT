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
        TCompletion&& completion)
    {
        _scheduler.ScheduleWithCompletion(std::forward<TWork>(work), std::forward<TCompletion>(completion));
    }

    template<typename TWork, typename TCompletion>
    requires Detail::ValidScheduleWithCompletion<TWork, TCompletion> void SystemScheduler::ScheduleWithCompletion(
        TWork&& work,
        TCompletion&& completion)
    {
        _asyncArena->execute(
            [&]()
            {
                _asyncTasks->run(
                    [work = std::make_shared<std::decay_t<TWork>>(std::forward<TWork>(work)),
                     completion = std::make_shared<std::decay_t<TCompletion>>(std::forward<TCompletion>(completion)),
                     this]()
                    {
                        auto result = (*work)();
                        _pendingCompletions.push(
                            [completion, result = std::move(result)](Timing::Timestamp delta, Catalogue cat) mutable
                            { (*completion)(delta, cat, std::move(result)); });
                    });
            });
    }
}
