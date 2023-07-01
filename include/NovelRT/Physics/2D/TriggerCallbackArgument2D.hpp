#ifndef NOVELRT_PHYSICS_PHYSICS2D_TRIGGERCALLBACKARGUMENT2D_H
#define NOVELRT_PHYSICS_PHYSICS2D_TRIGGERCALLBACKARGUMENT2D_H

#ifndef NOVELRT_PHYSICS_H
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct TriggerCallBackArgument2D final
    {
        const RigidBody2D* const RigidBody;
        const CollisionFixture2D* const CollisionFixture;
    };

} // namespace NovelRT::Physics::Physics2D

#endif // NOVELRT_PHYSICS_PHYSICS2D_TRIGGERCALLBACKARGUMENT2D_H