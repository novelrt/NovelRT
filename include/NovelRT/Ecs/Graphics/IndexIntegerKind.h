// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_INDEXINTEGERKIND_H
#define NOVELRT_ECS_GRAPHICS_INDEXINTEGERKIND_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    enum class IndexIntegerKind : uint32_t
    {
        UInt16,
        UInt32,
        UInt64,
        Int16,
        Int32,
        Int64
    };
}

#endif // NOVELRT_ECS_GRAPHICS_INDEXINTEGERKIND_H
