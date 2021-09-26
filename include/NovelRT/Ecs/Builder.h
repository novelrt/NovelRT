// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_BUILDER_H
#define NOVELRT_ECS_BUILDER_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class Builder
    {
    private:
        std::optional<SystemScheduler> _scheduler;

    public:
        Builder&
    };
}

#endif // NOVELRT_ECS_BUILDER_H
