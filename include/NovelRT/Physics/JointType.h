// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_JOINTTYPE_H
#define NOVELRT_PHYSICS_JOINTTYPE_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics
{
    enum class JointType
    {
        SpringJoint,
        MotorJoint
    };
}

#endif // !NOVELRT_PHYSICS_JOINTTYPE_H