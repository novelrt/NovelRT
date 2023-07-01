#pragma once

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class CapsuleCollisionFixture2D : public CollisionFixture2D
    {
    public:
        [[nodiscard]] virtual float GetHeight() = 0;

        [[nodiscard]] virtual float GetRadius() = 0;

        virtual void SetHeight(float height) = 0;

        virtual void SetRadius(float radius) = 0;
    };
}