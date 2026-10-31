#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Timing/Timestamp.hpp>

namespace NovelRT::Ecs
{
    class Catalogue;

    template <typename TComponent>
    class ComponentView;

    /**
     * @brief An interface declaration allowing for systems to be defined as C++ types.
     */
    class IEcsSystem
    {
    public:
        /**
         * @brief The system method. Your system's logic and behaviour goes in here.
         * @param now The current time (as of the start of the ECS update)
         * @param delta The delta time between the previous iteration and the current iteration.
         * @param catalogue The ECS catalogue object to provide thread-aware ComponentView<TComponent> instances.
         */
        virtual void Update(Timing::Timestamp now, Timing::Timestamp::duration delta, Catalogue catalogue) = 0;
        virtual ~IEcsSystem() = default;
    };
}
