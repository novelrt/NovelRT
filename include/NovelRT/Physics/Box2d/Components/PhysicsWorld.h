#ifndef NOVELRT_PHYSICS_BOX2D_PHYSICSWORLD_H
#define NOVELRT_PHYSICS_BOX2D_PHYSICSWORLD_H

#include <box2d/b2_world.h>

namespace NovelRT::Physics::Box2d
{
    struct PhysicsWorld
    {
        b2World* world;
        int32 velocityIterations, positionIterations;
        float accumilator;
        float stepTime;

        static const PhysicsWorld DeletedWorld;

        PhysicsWorld& operator+=(const PhysicsWorld& rhs)
        {
            world = rhs.world;
            velocityIterations = rhs.velocityIterations;
            positionIterations = rhs.positionIterations;
            accumilator = rhs.accumilator;
            stepTime = rhs.stepTime;
            return *this;
        }
    };

    const PhysicsWorld PhysicsWorld::DeletedWorld = PhysicsWorld{nullptr, -1, -1, NAN, NAN};
} // namespace NovelRT::Physics::Box2d
#endif // NOVELRT_PHYSICS_BOX2D_PHYSICSWORLD_H