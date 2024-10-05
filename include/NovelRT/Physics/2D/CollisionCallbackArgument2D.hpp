#pragma once

#ifndef NOVELRT_PHYSICS_HPP
#error NovelRT does not support including types explicitly by default. Please include Physics.h instead for the Physics namespace subset.
#endif

namespace NovelRT::Physics::Physics2D
{
    struct CollisionCallBackArgument2D final
    {
        const RigidBody2D* const RigidBody;
        const CollisionFixture2D* const CollisionFixture;
    };

} // namespace NovelRT::Physics::Physics2D