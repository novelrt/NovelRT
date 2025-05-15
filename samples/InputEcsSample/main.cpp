// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <memory>

#include <NovelRT/Graphics/Vulkan/VulkansGraphicsBackendTraits.hpp>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
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
        Configurator<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider<NovelRT::Graphics::Vulkan::VulkanGraphicsBackend>>())
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
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::Zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    scheduler.RegisterSystem([](auto delta, auto catalogue) {
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

        for (auto [entity, transform] : transforms)
        {
            TransformComponent newComponent{};
            newComponent.rotationInRadians = NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
            newComponent.scale = NovelRT::Maths::GeoVector2F::Zero();
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
    auto up = inputSystem->GetMappingId("Up");
    auto down = inputSystem->GetMappingId("Down");
    auto left = inputSystem->GetMappingId("Left");
    auto right = inputSystem->GetMappingId("Right");
    auto buttonA = inputSystem->GetMappingId("A");
    auto buttonB = inputSystem->GetMappingId("B");
    auto mouseClick = inputSystem->GetMappingId("LeftClick");

    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        ComponentView<NovelRT::Ecs::Input::InputEventComponent> events =
            catalogue.template GetComponentView<NovelRT::Ecs::Input::InputEventComponent>();
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();
        NovelRT::Maths::GeoVector2F scale = NovelRT::Maths::GeoVector2F::Zero();
        NovelRT::Maths::GeoVector2F move = NovelRT::Maths::GeoVector2F::Zero();

        NovelRT::Ecs::Input::InputEventComponent input;
        if (events.TryGetComponent(up, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            move += NovelRT::Maths::GeoVector2F{0.0f, 5.0f};
        }

        if (events.TryGetComponent(down, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            move += NovelRT::Maths::GeoVector2F{0.0f, -5.0f};
        }

        if (events.TryGetComponent(left, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            move += NovelRT::Maths::GeoVector2F{-5.0f, 0.0f};
        }

        if (events.TryGetComponent(right, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            move += NovelRT::Maths::GeoVector2F{5.0f, 0.0f};
        }

        if (events.TryGetComponent(buttonA, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            scale += NovelRT::Maths::GeoVector2F{0.2f, 0.2f};
        }

        if (events.TryGetComponent(buttonB, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            scale += NovelRT::Maths::GeoVector2F{-0.2f, -0.2f};
        }

        if (events.TryGetComponent(mouseClick, input) && input.state == KeyState::KeyDown)
        {
            logger.logInfo("Clicked at {}, {}", input.mousePositionX, input.mousePositionY);
        }

        for (auto [entity, transform] : transforms)
        {
            TransformComponent newComponent{};
            newComponent.scale = NovelRT::Maths::GeoVector2F::Zero();
            newComponent.scale += scale;
            newComponent.positionAndLayer += move;
            transforms.PushComponentUpdateInstruction(entity, newComponent);
        }
    });

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    logger.logInfoLine("Press the following:");
    logger.logInfoLine("W - Move Up");
    logger.logInfoLine("S - Move Down");
    logger.logInfoLine("A - Move Left");
    logger.logInfoLine("D - Move Right");
    logger.logInfoLine("K - Grow NovelChan");
    logger.logInfoLine("L - Shrink NovelChan");

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
