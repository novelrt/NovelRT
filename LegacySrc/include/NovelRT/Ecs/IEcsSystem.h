// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IECSSYSTEM_H
#define NOVELRT_IECSSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief An interface declaration allowing for systems to be defined as C++ types.
     */
    class IEcsSystem
    {
    public:
        /**
         * @brief The system method. Your system's logic and behaviour goes in here.
         * @param delta The delta time between the previous iteration and the current iteration, as a TimeStamp.
         * @param catalogue The ECS catalogue object to provide thread-aware ComponentView<TComponent> instances.
         */
        virtual void Update(Timing::Timestamp delta, Catalogue catalogue) = 0;
        virtual ~IEcsSystem() = default;
    };
}

#endif // NOVELRT_IECSSYSTEM_H
