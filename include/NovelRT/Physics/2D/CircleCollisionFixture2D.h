#ifndef NOVELRT_PHYSICS_PHYSICS2D_CIRCLECOLLISIONFIXTURE2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_CIRCLECOLLISIONFIXTURE2D_H

#ifndef NOVELRT_PHYSICS_H
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

#endif // NOVELRT_PHYSICS_PHYSICS2D_CIRCLECOLLISIONFIXTURE2D_H