#ifndef NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTURE2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTURE2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    class CapsuleCollisionFixture2D : public CollisionFixture2D
    {
    public:
        virtual float GetHeight() = 0;

        virtual float GetRadius() = 0;

        virtual void SetHeight(float height) = 0;

        virtual void SetRadius(float radius) = 0;
    };
}

#endif // NOVELRT_PHYSICS_PHYSICS2D_CAPSULECOLLISIONFIXTURE2D_H