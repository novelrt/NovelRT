#include <NovelRT/Physics/Box2d/Systems/Box2dSystem.h>

// TODO: replace with a proper transform component.
#include <NovelRT/Physics/Box2d/Components/TestTransform.h>

// TODO: make sure that the pool ID's for ECS are handled well, if needed.
// TODO: determine where inlining is appropriate.

namespace NovelRT::Physics::Box2d
{
    void Box2dSystem::UpdatePosition(NovelRT::Timing::Timestamp delta, NovelRT::Ecs::Catalogue catalogue)
    {
        auto physicsWorlds  = catalogue.GetComponentView<PhysicsWorld>();

        for(auto [entity, physicsWorld] : physicsWorlds)
        {
            PhysicsWorld pWorld = physicsWorld;

            // add time since last update to accumilator
            pWorld.accumilator += delta.getSecondsFloat();

            // when the acumilator becomes larger than the steptime a physics step will be done
            if(pWorld.accumilator < pWorld.stepTime)
            {
                physicsWorlds.PushComponentUpdateInstruction(entity, pWorld);
                continue;
            }

            pWorld.accumilator -= pWorld.stepTime;
            pWorld.world->Step(pWorld.stepTime, pWorld.velocityIterations, pWorld.positionIterations);
            physicsWorlds.PushComponentUpdateInstruction(entity, pWorld);
        }

        auto [transforms,physicsBodies] = catalogue.GetComponentViews<TestTransform, PhysicsBody>();

        for (auto [entity, physicsBody] : physicsBodies)
        {
            auto transform = transforms.GetComponent(entity);
            auto pBodyPos = physicsBody.body->GetPosition();
            transform.position = *reinterpret_cast<const NovelRT::Maths::GeoVector2F*>(&pBodyPos);
            transform.rotation = physicsBody.body->GetAngle();
            transforms.PushComponentUpdateInstruction(entity, transform);
        }
    }

    PhysicsWorld Box2dSystem::AddWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2World* const world, const float stepTime, const int32 velocityIterations, const int32 positionIterations)
    {
        auto pWorld = PhysicsWorld
        {
            world,
            velocityIterations, positionIterations,
            0,
            stepTime
        };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().PushComponentUpdateInstruction(0, worldEntityId, pWorld);
        return pWorld;
    }

    void Box2dSystem::RemoveWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId)
    {
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().PushComponentUpdateInstruction(0, worldEntityId, PhysicsWorld::DeletedWorld);
    }

    b2Body* Box2dSystem::AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* const bodyDef)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        return body;
    }

    b2Body* Box2dSystem::AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        return body;
    }

    b2Body* Box2dSystem::AddBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const b2BodyDef* bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        b2Body* body = pWorld.world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i)
        {
            body->CreateFixture(fixtureDef[i]);
        }
        return body;
    }

    b2Body* Box2dSystem::AddBody(b2World* const world, const b2BodyDef* const bodyDef)
    {
        return world->CreateBody(bodyDef);
    }

    b2Body* Box2dSystem::AddBody(b2World* const world, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef)
    {
        b2Body* body = world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        return body;
    }

    b2Body* Box2dSystem::AddBody(b2World* const world, const b2BodyDef* const bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount)
    {
        b2Body* body = world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i)
        {
            body->CreateFixture(fixtureDef[i]);
        }
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        auto body = pWorld.world->CreateBody(bodyDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef* const fixtureDef)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        auto body = pWorld.world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        auto body = pWorld.world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i)
        {
            body->CreateFixture(fixtureDef[i]);
        }
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef)
    {
        auto body = world->CreateBody(bodyDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef, const b2FixtureDef* const fixtureDef)
    {
        auto body = world->CreateBody(bodyDef);
        body->CreateFixture(fixtureDef);
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    b2Body* Box2dSystem::AddBodyComponent(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId, const b2BodyDef* const bodyDef, const b2FixtureDef** const fixtureDef, const int32_t fixtureCount)
    {
        auto body = world->CreateBody(bodyDef);
        for(int32_t i = 0; i < fixtureCount; ++i)
        {
            body->CreateFixture(fixtureDef[i]);
        }
        PhysicsBody pBody{ body };
        scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().PushComponentUpdateInstruction(0, entityId, pBody);   
        return body;
    }

    void Box2dSystem::AddBodyComponents(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId* const entityIds, b2Body** const bodies, const int32_t bodyCount)
    {
        auto pbBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        for(int32_t i = 0; i < bodyCount; ++i)
        {
            pbBuffer.PushComponentUpdateInstruction(0, entityIds[i], PhysicsBody{bodies[i]});
        }
    }

    void Box2dSystem::RemoveBody(b2World* const world, b2Body* const body)
    {
        world->DestroyBody(body);
    }


    void Box2dSystem::RemoveBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2Body* const body)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        pWorld.world->DestroyBody(body);
    }

    void Box2dSystem::RemoveEntityBody(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, const NovelRT::Ecs::EntityId entityId)
    {
        auto physicsBodyComponentBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        auto pBody = physicsBodyComponentBuffer.GetComponent(entityId);
        world->DestroyBody(pBody.body);
        physicsBodyComponentBuffer.PushComponentUpdateInstruction(0, entityId, PhysicsBody::DeletedBodyState);
    }

    void Box2dSystem::RemoveEntityBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, const NovelRT::Ecs::EntityId entityId)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        auto physicsBodyComponentBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        auto pBody = physicsBodyComponentBuffer.GetComponent(entityId);
        pWorld.world->DestroyBody(pBody.body);
        physicsBodyComponentBuffer.PushComponentUpdateInstruction(0, entityId, PhysicsBody::DeletedBodyState);
    }

    void Box2dSystem::RemoveBodies(b2World* const world, b2Body** const bodies, const int32_t bodyCount)
    {
        for (int32_t i = 0; i < bodyCount; i++)
        {
            world->DestroyBody(bodies[i]);
        }
    }

    void Box2dSystem::RemoveBodies(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, b2Body** const bodies, const int32_t bodyCount)
    {
        auto world = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId).world;
        for (int32_t i = 0; i < bodyCount; i++)
        {
            world->DestroyBody(bodies[i]);
        }
    }

    void Box2dSystem::RemoveEntityBodies(NovelRT::Ecs::SystemScheduler* const scheduler, b2World* const world, NovelRT::Ecs::EntityId* const entityIds, const int32_t entityCount)
    {
        auto pbBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        for (int32_t i = 0; i < entityCount; i++)
        {
            world->DestroyBody(pbBuffer.GetComponent(entityIds[i]).body);
        }
    }

    void Box2dSystem::RemoveEntityBodies(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId, NovelRT::Ecs::EntityId* const entityIds, const int32_t entityCount)
    {
        auto world = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId).world;
        auto pbBuffer = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>();
        for (int32_t i = 0; i < entityCount; i++)
        {
            world->DestroyBody(pbBuffer.GetComponent(entityIds[i]).body);
        }
    }

    b2World* Box2dSystem::GetWorld(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId worldEntityId)
    {
        auto pWorld = scheduler->GetComponentCache().GetComponentBuffer<PhysicsWorld>().GetComponent(worldEntityId);
        return pWorld.world;
    }

    b2Body* Box2dSystem::GetBody(NovelRT::Ecs::SystemScheduler* const scheduler, const NovelRT::Ecs::EntityId entityId)
    {
        auto pBody = scheduler->GetComponentCache().GetComponentBuffer<PhysicsBody>().GetComponent(entityId);
        return pBody.body;
    }
}