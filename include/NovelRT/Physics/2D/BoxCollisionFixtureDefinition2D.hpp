#pragma once

#ifndef NOVELRT_PHYSICS_HPP
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