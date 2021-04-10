#ifndef NOVELRT_PHYSICS_BOX2D_BOX2DSYSTEM_H
#define NOVELRT_PHYSICS_BOX2D_BOX2DSYSTEM_H

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include <NovelRT/Physics/Box2d/Components/PhysicsBody.h>
#include <NovelRT/Physics/Box2d/Components/PhysicsWorld.h>

#include <NovelRT.h>


namespace NovelRT::Physics::Box2d
{
    class Box2dSystem{
        private:
            static void UpdatePosition(NovelRT::Timing::Timestamp delta, NovelRT::Ecs::Catalogue catalogue);
        public:
            static PhysicsWorld AddWorld(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldEntityId, b2World* world, float stepTime, int32 velocityIterations = 6, int32 positionIterations = 2);
            
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* scheduler, const NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef);
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* scheduler, const NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef);
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* scheduler, const NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, const int32_t fixtureCount);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* bodyDef);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, const int32_t fixtureCount);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId,const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, int32_t fictureCount);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, b2World* const world, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, b2World* const world, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef);
            static PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, b2World* const world, NovelRT::Ecs::EntityId entityId,const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, int32_t fictureCount);
            static void RemoveBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId,b2Body* body);
            static void RemoveEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId);

            static void RegisterSystem(NovelRT::Ecs::SystemScheduler* scheduler){
                scheduler->RegisterSystem(UpdatePosition);
            }
    };
}

#endif // NOVELRT_PHYSICS_BOX2D_BOX2DSYSTEM_H