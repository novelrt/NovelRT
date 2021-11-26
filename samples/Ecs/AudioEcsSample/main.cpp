// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <time.h>

using namespace NovelRT::Ecs::Audio;

int main(int, char*[])
{
    // RNG
    srand(time(NULL));

    // Old resources setup
    std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
    std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
    std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
    std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";

    // Button setup - old way
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> fadeMusicOutButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> fadeMusicOutInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> fadeMusicOutText;

    std::unique_ptr<NovelRT::Graphics::BasicFillRect> fadeMusicInButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> fadeMusicInInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> fadeMusicInText;

    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playLaz0rButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playLaz0rInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playLaz0rText;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playGoatButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playGoatInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playGoatText;

    // Setup of NovelRunner
    auto runner = NovelRT::NovelRunner(0, "NovelRT - Audio ECS Sample", NovelRT::Windowing::WindowMode::Windowed);
    auto console = NovelRT::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_APP);
    auto loggingLevel = NovelRT::LogLevel::Debug;
    runner.getDebugService()->setIsFpsCounterVisible(false);
    runner.getRenderer()->setBackgroundColour(NovelRT::Graphics::RGBAColour(103, 128, 159, 255));

    // Creating the UI
    auto playButtonTransform = NovelRT::Transform(NovelRT::Maths::GeoVector2F((1920 / 2), (1080 / 2)), 0,
                                                  NovelRT::Maths::GeoVector2F(200, 200));
    bool paused = false;

    // fade music in button
    auto fadeMusicInTransform = playButtonTransform;
    fadeMusicInTransform.position.x += (1920 / 3);
    fadeMusicInButton = runner.getRenderer()->createBasicFillRect(
        fadeMusicInTransform, 3, NovelRT::Graphics::RGBAColour(rand() % 255, rand() % 255, rand() % 255, 255));
    auto fadeMusicInTextTransform = fadeMusicInTransform;
    fadeMusicInTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    fadeMusicInText =
        runner.getRenderer()->createTextRect(fadeMusicInTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255),
                                             36, (fontsDirPath / "Gayathri-Regular.ttf").string());
    fadeMusicInText->setText("Fade In");
    fadeMusicInInteraction = runner.getInteractionService()->createBasicInteractionRect(fadeMusicInTransform, 2);
    fadeMusicInInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    // fade music out button
    auto fadeMusicOutTransform = playButtonTransform;
    fadeMusicOutTransform.position.x -= (1920 / 3);
    fadeMusicOutButton = runner.getRenderer()->createBasicFillRect(
        fadeMusicOutTransform, 3, NovelRT::Graphics::RGBAColour(rand() % 255, rand() % 255, rand() % 255, 255));
    auto fadeMusicOutTextTransform = fadeMusicOutTransform;
    fadeMusicOutTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    fadeMusicOutText =
        runner.getRenderer()->createTextRect(fadeMusicOutTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255),
                                             36, (fontsDirPath / "Gayathri-Regular.ttf").string());
    fadeMusicOutText->setText("Fade Out");
    fadeMusicOutInteraction = runner.getInteractionService()->createBasicInteractionRect(fadeMusicOutTransform, 2);
    fadeMusicOutInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    auto laz0rButtonTransform = playButtonTransform;
    laz0rButtonTransform.position.y += (1080 / 3);
    playLaz0rButton = runner.getRenderer()->createBasicFillRect(laz0rButtonTransform, 3,
                                                                NovelRT::Graphics::RGBAColour(255, 0, 0, 255));
    auto playLaz0rTextTransform = laz0rButtonTransform;
    playLaz0rTextTransform.position.x -= 50;
    playLaz0rTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    playLaz0rText =
        runner.getRenderer()->createTextRect(playLaz0rTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playLaz0rText->setText("Pew");
    playLaz0rInteraction = runner.getInteractionService()->createBasicInteractionRect(laz0rButtonTransform, 2);
    playLaz0rInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    auto goatButtonTransform = playButtonTransform;
    goatButtonTransform.position.x += (1920 / 4);
    goatButtonTransform.position.y += (1080 / 3);
    playGoatButton = runner.getRenderer()->createBasicFillRect(goatButtonTransform, 3,
                                                               NovelRT::Graphics::RGBAColour(160, 0, 160, 255));
    auto playGoatTextTransform = goatButtonTransform;
    playGoatTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    playGoatText =
        runner.getRenderer()->createTextRect(playGoatTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playGoatText->setText("Welp.");
    playGoatInteraction = runner.getInteractionService()->createBasicInteractionRect(goatButtonTransform, 2);
    playGoatInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    // Setup of ECS
    auto audioSystem = std::make_shared<NovelRT::Ecs::Audio::AudioSystem>();
    auto scheduler = NovelRT::Ecs::Configurator().InitialiseAndRegisterComponents();
    scheduler.RegisterSystem(audioSystem);
    auto deleteState = AudioEmitterComponent();
    scheduler.GetComponentCache().RegisterComponentType(deleteState);
    scheduler.GetComponentCache().RegisterComponentType(AudioEmitterStateComponent{AudioEmitterState::Done});

    // Setup of entities and components
    std::string waltzPath = (soundsDirPath / "waltz.ogg").string();
    std::string laz0rPath = (soundsDirPath / "laz0r.ogg").string();
    std::string goatPath = (soundsDirPath / "goat.ogg").string();
    auto waltzHandle = audioSystem->CreateAudio(waltzPath, true);
    auto laz0rHandle = audioSystem->CreateAudio(laz0rPath, false);
    auto goatHandle = audioSystem->CreateAudio(goatPath, false);
    AudioEmitterComponent waltzComponent = AudioEmitterComponent{waltzHandle, true, -1, 0.75f};
    AudioEmitterStateComponent waltzState = AudioEmitterStateComponent{AudioEmitterState::Stopped, 5.0};
    // Now the sound components
    AudioEmitterComponent laz0r = AudioEmitterComponent{laz0rHandle, false, 0, 0.75f};
    AudioEmitterComponent goat = laz0r;
    goat.handle = goatHandle;
    goat.volume = 1.0f; // o no

    // Setup of entities and components
    auto entities = NovelRT::Ecs::EntityCache(3);
    scheduler.GetEntityCache() = entities;
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
        0, 0, waltzComponent);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 0, waltzState);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 1,
                                                                                                             laz0r);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 1, AudioEmitterStateComponent{AudioEmitterState::Stopped});

    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 2,
                                                                                                             goat);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 2, AudioEmitterStateComponent{AudioEmitterState::Stopped});

    fadeMusicOutInteraction->Interacted += [&] {
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 0, AudioEmitterStateComponent{AudioEmitterState::ToFadeOut, 5.0f, 0.0f});
        console.logDebugLine("Fading music out!");
    };

    fadeMusicInInteraction->Interacted += [&] {
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 0, AudioEmitterStateComponent{AudioEmitterState::ToFadeIn, 5.0f, 0.75f});
        console.logDebugLine("Fading music in!");
    };

    playLaz0rInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 1 - I'ma firin' mah laz0r!");
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 1, AudioEmitterStateComponent{AudioEmitterState::ToPlay});
    };

    playGoatInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 2 - AHHHHHHHHHHHHHHHHHHHHHHHH");
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 2, AudioEmitterStateComponent{AudioEmitterState::ToPlay});
    };

    runner.Update += [&](NovelRT::Timing::Timestamp delta) { scheduler.ExecuteIteration(delta); };

    runner.SceneConstructionRequested += [&] {
        fadeMusicInButton->executeObjectBehaviour();
        fadeMusicOutButton->executeObjectBehaviour();
        playLaz0rButton->executeObjectBehaviour();
        playGoatButton->executeObjectBehaviour();
        fadeMusicInText->executeObjectBehaviour();
        fadeMusicOutText->executeObjectBehaviour();
        playLaz0rText->executeObjectBehaviour();
        playGoatText->executeObjectBehaviour();
        fadeMusicInInteraction->executeObjectBehaviour();
        fadeMusicOutInteraction->executeObjectBehaviour();
        playLaz0rInteraction->executeObjectBehaviour();
        playGoatInteraction->executeObjectBehaviour();
    };

    runner.runNovel();

    return 0;
}
