#ifndef NOVELRT_PHYSICS_PHYSICS2D_BOXCOLLISIONFIXTUREDEFINITION2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_BOXCOLLISIONFIXTUREDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct BoxCollisionFixtureDefinition2D final : public CollisionFixtureDefinition2D
    {
        NovelRT::Maths::GeoVector2F HalfSize;

        ~BoxCollisionFixtureDefinition2D() = default;
    };
}

#endif // NOVELRT_PHYSICS_PHYSICS2D_BOXCOLLISIONFIXTUREDEFINITION2D_H