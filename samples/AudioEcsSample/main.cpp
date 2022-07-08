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

// Default Provider Initialisation
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

// Initialisation of ECS Audio System
    auto audioSystem = std::make_shared<NovelRT::Ecs::Audio::AudioSystem>();
    scheduler.RegisterSystem(audioSystem);
    auto deleteState = AudioEmitterComponent();
    scheduler.GetComponentCache().RegisterComponentType(deleteState, "NovelRT::Ecs::Audio::AudioEmitterComponent");
    scheduler.GetComponentCache().RegisterComponentType(AudioEmitterStateComponent{AudioEmitterState::Done}, "NovelRT::Ecs::Audio::AudioEmitterStateComponent");

// Get the Sounds resource directory
    auto rootDir = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>()->GetResourceLoader()->ResourcesRootDirectory();
    auto soundDir = rootDir / "Sounds";

// Create the sound components
    std::string uwu = (soundDir / "uwu.ogg").string();
    auto uwuHandle = audioSystem->CreateAudio(uwu, true);
    AudioEmitterComponent uwuComponent = AudioEmitterComponent{uwuHandle, true, -1, 0.75f};
    AudioEmitterStateComponent uwuState = AudioEmitterStateComponent{AudioEmitterState::Stopped, 5.0};

    std::string ahh = (soundDir / "goat.ogg").string();
    auto goatHandle = audioSystem->CreateAudio(ahh, false);
    AudioEmitterComponent goatComponent = AudioEmitterComponent{goatHandle, false, -1, 0.75f};
    AudioEmitterStateComponent goatState = AudioEmitterStateComponent{AudioEmitterState::Stopped, 5.0};

// Assign the entities holding the components
    auto& entityFactory = NovelRT::AtomFactoryDatabase::GetFactory("EntityId");
    auto musicEnt = entityFactory.GetNext();
    auto soundEnt = entityFactory.GetNext();

    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
        musicEnt, 0, uwuComponent);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        musicEnt, 0, uwuState);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
        soundEnt, 0, goatComponent);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        soundEnt, 0, goatState);

// Rendering Initialisation
    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    renderingSystem->BackgroundColour() = NovelRT::Graphics::RGBAColour(248,248,255,255);

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("uwu");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    NovelRT::Maths::GeoBounds uwuBounds = NovelRT::Maths::GeoBounds(NovelRT::Maths::GeoVector2F::zero(), NovelRT::Maths::GeoVector2F(textureFuture.GetBackingConcurrentSharedPtr()->width, textureFuture.GetBackingConcurrentSharedPtr()->height), 0);
    bool uwuFlip = false;

    transformBuffer.PushComponentUpdateInstruction(
        0, parentEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});

    scheduler.RegisterSystem([&uwuBounds, &uwuFlip](auto delta, auto catalogue) {
        ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

        for (auto [entity, transform] : transforms)
        {
            TransformComponent newComponent{};
            newComponent.positionAndLayer = NovelRT::Maths::GeoVector3F::zero();
            if(uwuFlip)
            {
                newComponent.positionAndLayer.x = 2;
                uwuBounds = NovelRT::Maths::GeoBounds(NovelRT::Maths::GeoVector2F(transform.positionAndLayer.x+2, transform.positionAndLayer.y), uwuBounds.size, transform.rotationInRadians);
                if (transform.positionAndLayer.x >= 480)
                {
                    uwuFlip = false;
                }
            }
            else
            {
                newComponent.positionAndLayer.x = -2;
                uwuBounds = NovelRT::Maths::GeoBounds(NovelRT::Maths::GeoVector2F(transform.positionAndLayer.x-2, transform.positionAndLayer.y), uwuBounds.size, transform.rotationInRadians);
                if (transform.positionAndLayer.x <= -480)
                {
                    uwuFlip = true;
                }
            }
            newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
            newComponent.rotationInRadians = 0;
            transforms.PushComponentUpdateInstruction(entity, newComponent);
        }
    });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("ECS Audio Test");

// Input initialisation
    std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Input::InputSystem>();

    inputSystem->AddDefaultKBMMapping();
    auto mouseClick = inputSystem->GetMappingId("LeftClick");

// Register system to restart music if it stops
    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        auto [emitters, states] = catalogue.template GetComponentViews<AudioEmitterComponent, AudioEmitterStateComponent>();
        for (auto [entity, emitter] : emitters)
        {
            if(emitter.isMusic)
            {
                auto state = states.GetComponent(entity);
                if(state.state == AudioEmitterState::Stopped)
                {
                    AudioEmitterStateComponent newState{};
                    newState.fadeDuration = 3.0f;
                    newState.fadeExpectedVolume = 0.75f;
                    newState.state = AudioEmitterState::ToFadeIn;
                    states.PushComponentUpdateInstruction(entity, newState);
                }
            }
        }
    });

// Register system to trigger sound when something is clicked
    scheduler.RegisterSystem([&](auto delta, auto catalogue) {
        ComponentView<NovelRT::Ecs::Input::InputEventComponent> events =
            catalogue.template GetComponentView<NovelRT::Ecs::Input::InputEventComponent>();

        NovelRT::Ecs::Input::InputEventComponent input;
        bool triggered = false;
        if (events.TryGetComponent(mouseClick, input) &&
            (input.state == KeyState::KeyDown || input.state == KeyState::KeyDownHeld))
        {
            triggered = uwuBounds.pointIsWithinBounds(NovelRT::Maths::GeoVector2F(input.mousePositionX, input.mousePositionY));
        }

        if(triggered)
        {
            logger.logInfoLine("Clicked!");
            //auto emitters = catalogue.template GetComponentView<AudioEmitterComponent>();
            //auto states = catalogue.template GetComponentView<AudioEmitterStateComponent>();
            // for(auto [entity, emitter] : emitters)
            // {
            //     if(!emitter.isMusic)
            //     {
            //         AudioEmitterStateComponent state;
            //         if(states.TryGetComponent(entity, state))
            //         {
            //             if(state.state == AudioEmitterState::Stopped)
            //             {
            //                 state.state = AudioEmitterState::ToPlay;
            //                 states.PushComponentUpdateInstruction(entity, state);
            //                 logger.logDebugLine("Setting back to play!");
            //             }
            //         }
            //     }
            // }

        }
    });

// Additional setup to ensure ECS works
    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    logger.logInfoLine("Click within the UwU face to play your sound!");

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
