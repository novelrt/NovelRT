#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct PolygonCollisionFixtureDefinition2D final : public CollisionFixtureDefinition2D
    {
        std::vector<NovelRT::Maths::GeoVector2F> Vertices;

        ~PolygonCollisionFixtureDefinition2D() = default;
    };

} // namespace NovelRT::Physics::Physics2D