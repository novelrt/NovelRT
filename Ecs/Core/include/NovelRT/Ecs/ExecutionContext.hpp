#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <cstddef>

namespace NovelRT::Ecs
{
    class SystemScheduler;

    struct ExecutionContext
    {
        SystemScheduler& _scheduler;
        size_t _poolId;
    };
}