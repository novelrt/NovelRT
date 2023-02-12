// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PHYSICS_PHYSICS2D_SPRINGJOINTDEFINITION2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_SPRINGJOINTDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct SpringJointDefinition2D final : public JointDefinition2D
    {
        float MinLength;
        float MaxLength;
        float RestLength;
        float Stiffness;
        float Damping;

        ~SpringJointDefinition2D() = default;
    };
}

#endif // !NOVELRT_PHYSICS_PHYSICS2D_SPRINGJOINTDEFINITION2D_H