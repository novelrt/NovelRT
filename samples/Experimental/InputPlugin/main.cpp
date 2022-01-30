// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <memory>

using namespace NovelRT::Experimental::Input::Glfw;
using namespace NovelRT::Experimental::Input;

using namespace NovelRT::Ecs;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(inputProvider)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childOfChildEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(
        0, childEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    scheduler.RegisterSystem([](auto delta, auto catalogue) {
                                 ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

                                 for (auto [entity, transform] : transforms)
                                 {
                                     TransformComponent newComponent{};
                                     newComponent.rotationInRadians = NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
                                     newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
                                     transforms.PushComponentUpdateInstruction(entity, newComponent);
                                 }
                             });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("ECS Input Test");

    std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Input::InputSystem>();

    inputSystem->AddDefaultKBMMapping();

    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
                                 ComponentView<NovelRT::Ecs::Input::InputEventComponent> events = catalogue.GetComponentView<NovelRT::Ecs::Input::InputEventComponent>();
                                 ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();
                                 NovelRT::Maths::GeoVector2F scale = NovelRT::Maths::GeoVector2F::zero();
                                 NovelRT::Maths::GeoVector2F move = NovelRT::Maths::GeoVector2F::zero();

                                 for (auto [entity, input] : events)
                                 {
                                     //movement
                                     if(inputSystem->GetMappingName(entity) == "Down" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         move += NovelRT::Maths::GeoVector2F{0.0f, -5.0f};
                                     }
                                     if(inputSystem->GetMappingName(entity) == "Up" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         move += NovelRT::Maths::GeoVector2F{0.0f, 5.0f};
                                     }
                                     if(inputSystem->GetMappingName(entity) == "Left" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         move += NovelRT::Maths::GeoVector2F{-5.0f, 0.0f};
                                     }
                                     if(inputSystem->GetMappingName(entity) == "Right" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         move += NovelRT::Maths::GeoVector2F{5.0f, 0.0f};
                                     }

                                     //scale
                                     if(inputSystem->GetMappingName(entity) == "A" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         scale += NovelRT::Maths::GeoVector2F{0.2f, 0.2f};
                                     }
                                     if(inputSystem->GetMappingName(entity) == "B" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         scale += NovelRT::Maths::GeoVector2F{-0.2f, -0.2f};
                                     }

                                     if(inputSystem->GetMappingName(entity) == "LeftClick" && (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
                                     {
                                         logger.logInfo("Clicked at {}, {}", input.mousePositionX, input.mousePositionY);
                                     }
                                 }

                                 for (auto [entity, transform] : transforms)
                                 {
                                     TransformComponent newComponent{};
                                     newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
                                     newComponent.scale += scale;
                                     newComponent.positionAndLayer += move;
                                     transforms.PushComponentUpdateInstruction(entity, newComponent);
                                 }
                             });

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    logger.logInfoLine("\n\n\nPress the following:\nW - Move Up\nS - Move Down\nA - Move Left\nD - Move Right\nK - Grow\nL - Shrink");

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
