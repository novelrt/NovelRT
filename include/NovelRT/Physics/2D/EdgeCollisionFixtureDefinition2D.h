#ifndef NOVELRT_PHYSICS_PHYSICS2D_EDGECOLLISIONFIXTUREDEFINITION2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_EDGECOLLISIONFIXTUREDEFINITION2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct EdgeCollisionFixtureDefinition2D final : CollisionFixtureDefinition2D
    {
        std::array<NovelRT::Maths::GeoVector2F> Vertices;

        ~EdgeCollisionFixtureDefinition2D() = default;
    };
    
} // namespace NovelRT::Physics::Physics2D

#endif // NOVELRT_PHYSICS_PHYSICS2D_EDGECOLLISIONFIXTUREDEFINITION2D_H