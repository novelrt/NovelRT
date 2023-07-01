#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class BoxCollisionFixture2D : public CollisionFixture2D
    {
    public:
        [[nodiscard]] virtual NovelRT::Maths::GeoVector2F GetHalfSize() = 0;

        virtual void SetHalfSize(NovelRT::Maths::GeoVector2F halfSize) = 0;
    };
}