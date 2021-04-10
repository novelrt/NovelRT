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
            static PhysicsWorld AddWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2World* const world, const float stepTime, const int32 velocityIterations = 6, const int32 positionIterations = 2);
            static void RemoveWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId);
            
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* const bodyDef);
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef);
            static b2Body* AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* const bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* const bodyDef);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef);
            static b2Body* AddBody(b2World* const world, const b2BodyDef* const bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef* const fixtureDef);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef);
            static b2Body* AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount);
            
            static void AddBodyComponents(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId* const entityIds, b2Body** const bodies, const int32_t bodyCount);
            
            static void RemoveBody(b2World* const world, b2Body* const body);
            static void RemoveBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2Body* const body);
            static void RemoveEntityBody(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId);
            static void RemoveEntityBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId);
            
            static void RemoveBodies(b2World* const world, b2Body** const bodies, const int32_t bodyCount);
            static void RemoveBodies(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2Body** const bodies, const int32_t bodyCount);
            static void RemoveEntityBodies(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, NovelRT::Ecs::EntityId* const entityIds, const int32_t entityCount);
            static void RemoveEntityBodies(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, NovelRT::Ecs::EntityId* const entityIds, const int32_t entityCount);

            static b2World* GetWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId);
            static b2Body* GetBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId entityId);

            static void RegisterSystem(NovelRT::Ecs::SystemScheduler* const scheduler){
                scheduler->RegisterSystem(UpdatePosition);
            }
    };
}

#endif // NOVELRT_PHYSICS_BOX2D_BOX2DSYSTEM_H