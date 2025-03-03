#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct CollisionFixtureDefinition2D
    {
        NovelRT::Maths::GeoVector2F Offset;
        float Friction;
        float Restitution;
        float RestitutionThreshold;
        float Density;
        bool IsSensor;

        virtual ~CollisionFixtureDefinition2D() = 0;
    };

} // namespace NovelRT::Physics::Physics2D