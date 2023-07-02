#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct CircleCollisionFixtureDefinition2D final : public CollisionFixtureDefinition2D
    {
        float Radius;

        ~CircleCollisionFixtureDefinition2D() = default;
    };

} // namespace NovelRT::Physics::Physics2D