#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

namespace NovelRT
{
    namespace Timing
    {
        class Timestamp;
    }

    namespace Ecs
    {
        class Catalogue;
    }
}

namespace NovelRT::Ecs::Detail
{
    template<typename TWork, typename TCompletion>
    concept ValidScheduleWithCompletion =
        std::invocable<TWork> && std::invocable<TCompletion, Timing::Timestamp, Catalogue, std::invoke_result_t<TWork>>;
}