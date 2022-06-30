// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <memory>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Audio;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

#if NOVELRT_MOLTENVK_VENDORED
    auto icdPath = NovelRT::Utilities::Misc::getExecutablePath() / "MoltenVK_icd.json";
    setenv("VK_ICD_FILENAMES", icdPath.c_str(), 0);
    logger.logInfo("macOS detected - setting VK_ICD_FILENAMES to path: {}", icdPath.c_str());
#endif

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

    auto audioSystem = std::make_shared<NovelRT::Ecs::Audio::AudioSystem>();
    scheduler.RegisterSystem(audioSystem);
    auto deleteState = AudioEmitterComponent();
    scheduler.GetComponentCache().RegisterComponentType(deleteState, "NovelRT::Ecs::Audio::AudioEmitterComponent");
    scheduler.GetComponentCache().RegisterComponentType(AudioEmitterStateComponent{AudioEmitterState::Done}, "NovelRT::Ecs::Audio::AudioEmitterStateComponent");

    auto rootDir = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>()->GetResourceLoader()->ResourcesRootDirectory();
    auto soundDir = rootDir / "sounds";

    std::string uwu = (soundDir / "uwu.ogg").string();
    auto uwuHandle = audioSystem->CreateAudio(uwu, true);
    AudioEmitterComponent uwuComponent = AudioEmitterComponent{uwuHandle, true, -1, 0.75f};
    AudioEmitterStateComponent uwuState = AudioEmitterStateComponent{AudioEmitterState::Stopped, 5.0};

    auto entities = NovelRT::Ecs::EntityCache(1);
    scheduler.GetEntityCache() = entities;
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
        0, 0, uwuComponent);
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 0, uwuState);

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
    auto mouseClick = inputSystem->GetMappingId("LeftClick");

    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        ComponentView<NovelRT::Ecs::Input::InputEventComponent> events =
            catalogue.template GetComponentView<NovelRT::Ecs::Input::InputEventComponent>();
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();
        std::vector<NovelRT::Maths::GeoVector3F> bounds = std::vector<NovelRT::Maths::GeoVector3F>();
        NovelRT::Maths::GeoVector2F scale = NovelRT::Maths::GeoVector2F::zero();
        NovelRT::Maths::GeoVector2F move = NovelRT::Maths::GeoVector2F::zero();
        bool triggered = false;
        bool willCalculate = false;

        for (auto [entity, transform] : transforms)
        {
            bounds.emplace_back(transform.positionAndLayer);
        }

        if(bounds.size() == 3)
        {
            willCalculate = true;
        }

        NovelRT::Ecs::Input::InputEventComponent input;
        if (events.TryGetComponent(mouseClick, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld)
            && willCalculate)
        {
            auto p = NovelRT::Maths::GeoVector3F{input.mousePositionX, input.mousePositionY, 0};

            auto p0 = bounds[0];
            auto p1 = bounds[1];
            auto p2 = bounds[2];

            auto s = (p0.x - p2.x) * (p.y - p2.y) - (p0.y - p2.y) * (p.x - p2.x);
            auto t = (p1.x - p0.x) * (p.y - p0.y) - (p1.y - p0.y) * (p.x - p0.x);

            if ((s < 0) != (t < 0) && s != 0 && t != 0)
            {
            }
            else
            {
                auto d = (p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x);
                if(d == 0 || (d < 0) == (s + t <= 0))
                {
                    triggered = true;
                }
            }
        }

        if(triggered)
        {
            catalogue.template GetComponentView<NovelRT::Ecs::Audio::AudioEmitterStateComponent>();
            ComponentView<AudioEmitterStateComponent> states = catalogue.template GetComponentView<AudioEmitterStateComponent>();
            for(auto [entity, state] : states)
            {
                if(state.state == AudioEmitterState::Playing)
                {
                    states.PushComponentUpdateInstruction(entity, AudioEmitterStateComponent{AudioEmitterState::ToFadeIn, 5.0f, 0.75f});
                    logger.logDebugLine("Now fading in!");
                }
                else if(state.state == AudioEmitterState::Stopped)
                {
                    states.PushComponentUpdateInstruction(entity, AudioEmitterStateComponent{AudioEmitterState::ToFadeOut, 5.0f, 0.0f});
                    logger.logDebugLine("Now fading out!");
                }
            }
        }
    });

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    logger.logInfoLine("Click within the Novel-chan triad to play your sound!");
    
    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
