#include <NovelRT/Physics/Box2d/Systems/Box2dSystem.h>
#include <NovelRT/Physics/Box2d/Components/PhysicsBody.h>
#include <NovelRT/Physics/Box2d/Components/TestTransform.h>
#include <NovelRT/Physics/Box2d/Components/PhysicsWorld.h>
#include <NovelRT.h>

namespace NovelRT::Physics::Box2d
{
    void Box2dSystem::UpdateWorld(NovelRT::Timing::Timestamp delta, NovelRT::Ecs::Catalogue catalogue){
        auto [physicsWorlds] = catalogue.GetComponentViews<PhysicsWorld>();

        for(auto [entity, physicsWorld] : physicsWorlds)
        {
            PhysicsWorld pWorld = physicsWorld;

            // add time since last update to accumilator
            pWorld.accumilator += delta.getSecondsFloat();

            // when the acumilator becomes larger than the steptime a physics step will be done
            if(pWorld.accumilator < pWorld.stepTime){
                return;
            }

            pWorld.accumilator -= pWorld.stepTime;
            pWorld.world->Step(pWorld.stepTime,pWorld.velocityIterations,pWorld.positionIterations);
            physicsWorlds.PushComponentUpdateInstruction(entity,pWorld);
        }
    }

    void Box2dSystem::UpdatePosition(NovelRT::Timing::Timestamp, NovelRT::Ecs::Catalogue catalogue){
        auto [transforms,physicsBodies] = catalogue.GetComponentViews<TestTransform,PhysicsBody>();

        for (auto [entity, physicsBody] : physicsBodies)
        {
            auto transform = transforms.GetComponent(entity);
            auto pBodyPos = physicsBody.body->GetPosition();
            transform.position = *reinterpret_cast<const NovelRT::Maths::GeoVector2F*>(&pBodyPos);
            transform.rotation = physicsBody.body->GetAngle();
            transforms.PushComponentUpdateInstruction(entity,transform);
        }
    }

    NovelRT::Ecs::EntityId CreateWorld(NovelRT::Ecs::SystemScheduler* scheduler, b2Vec2 gravity, float stepTime, int32 velocityIterations = 6, int32 positionIterations = 2){
        auto entityId = NovelRT::Ecs::EntityId::getNextEntityId();
        auto pWorld = PhysicsWorld{
            new b2World(gravity),
            velocityIterations, positionIterations,
            0,
            stepTime
        };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().PushComponentUpdateInstruction(0,entityId,pWorld);
        return entityId;
    }

    b2Body* AddBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        return body;
    }

    b2Body* Box2dSystem::AddBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        return body;
    }

    b2Body* Box2dSystem::AddBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, int32_t fixtureCount){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i){
            body->CreateFixture(fixtureDef[i]);
        }
        return body;
    }

    PhysicsBody AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        auto body = pWorld.world->CreateBody(bodyDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0,entityId,pBody);   
        return pBody;
    }

    PhysicsBody Box2dSystem::AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        auto body = pWorld.world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0,entityId,pBody);   
        return pBody;
    }

    PhysicsBody Box2dSystem::AddEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef** fixtureDef, int32_t fixtureCount){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        auto body = pWorld.world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i){
            body->CreateFixture(fixtureDef[i]);
        }
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0,entityId,pBody);   
        return pBody;
    }

    void Box2dSystem::RemoveBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, b2Body* body){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        pWorld.world->DestroyBody(body);
    }

    void Box2dSystem::RemoveEntityBody(NovelRT::Ecs::SystemScheduler* scheduler, NovelRT::Ecs::EntityId worldId, const NovelRT::Atom entityId){
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldId);
        auto physicsBodyComponentBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        auto pBody = physicsBodyComponentBuffer.GetComponent(entityId);
        pWorld.world->DestroyBody(pBody.body);
        physicsBodyComponentBuffer.PushComponentUpdateInstruction(0,entityId,PhysicsBody::DeletedBodyState);
    }
}