#ifndef NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTUREDEFINITION2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTUREDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct CapsuleCollisionFixtureDefinition2D final : public CollisionFixtureDefinition2D
    {
        float Height;
        float Radius;

        ~CapsuleCollisionFixtureDefinition2D() = default;
    };
}

#endif // NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTUREDEFINITION2D_H