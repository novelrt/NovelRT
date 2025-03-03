#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class CircleCollisionFixture2D : public CollisionFixture2D
    {
        [[nodiscard]] virtual float GetRadius() = 0;

        virtual void SetRadius() = 0;
    };

} // namespace NovelRT::Physics::Physics2D