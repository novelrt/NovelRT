#ifndef NOVELRT_PHYSICS_BOX2D_PHYSICSBODY_H
#define NOVELRT_PHYSICS_BOX2D_PHYSICSBODY_H

#include <box2d/b2_body.h>

namespace NovelRT::Physics::Box2d
{
    struct PhysicsBody
    {
        b2Body* body;

        static const PhysicsBody DeletedBodyState;

        PhysicsBody& operator+=(const PhysicsBody& rhs)
        {
            body = rhs.body;
            return *this;
        }
    };

    const PhysicsBody PhysicsBody::DeletedBodyState = PhysicsBody{nullptr};
} // namespace NovelRT::Physics::Box2d

#endif // NOVELRT_PHYSICS_BOX2D_PHYSICSBODY_H