// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

using namespace NovelRT::Ecs::Audio;

int main(int /*argc*/, char* /*argv*/[])
{
    // Old resources setup
    std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
    std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
    std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
    std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";

    // Button setup - old way
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playMusicButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playMusicInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playMusicText;

    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playNaniButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playNaniInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playNaniText;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playLazerButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playLazerInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playLazerText;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playGoatButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playGoatInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playGoatText;

    // Setup of NovelRunner
    auto runner = NovelRT::NovelRunner(0, "NovelRT - Audio ECS Sample", NovelRT::Windowing::WindowMode::Windowed);
    auto console = NovelRT::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_APP);
    auto loggingLevel = NovelRT::LogLevel::Debug;
    runner.getDebugService()->setIsFpsCounterVisible(true);
    runner.getRenderer()->setBackgroundColour(NovelRT::Graphics::RGBAColour(103, 128, 159, 255));

    // Creating the UI
    auto playButtonTransform = NovelRT::Transform(NovelRT::Maths::GeoVector2F((1920 / 2), (1080 / 2)), 0,
                                                  NovelRT::Maths::GeoVector2F(200, 200));
    playMusicButton = runner.getRenderer()->createBasicFillRect(playButtonTransform, 3,
                                                                NovelRT::Graphics::RGBAColour(0, 255, 0, 255));
    auto playMusicTextTransform = playButtonTransform;
    playMusicTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    auto vec = playButtonTransform.position;
    vec.x = playButtonTransform.position.x - 75;
    playMusicTextTransform.position = vec;
    playMusicText =
        runner.getRenderer()->createTextRect(playMusicTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playMusicText->setText("Play / Pause");
    playMusicInteraction = runner.getInteractionService()->createBasicInteractionRect(playButtonTransform, 2);
    playMusicInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;
    bool paused = false;

    auto naniButtonTransform = playButtonTransform;
    naniButtonTransform.position.x -= (1920 / 4);
    naniButtonTransform.position.y += (1080 / 3);
    playNaniButton = runner.getRenderer()->createBasicFillRect(naniButtonTransform, 3,
                                                               NovelRT::Graphics::RGBAColour(160, 0, 0, 255));
    auto playNaniTextTransform = naniButtonTransform;
    playNaniTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    playNaniTextTransform.position.x -= 50;
    playNaniText =
        runner.getRenderer()->createTextRect(playNaniTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playNaniText->setText("Nani!?");
    playNaniInteraction = runner.getInteractionService()->createBasicInteractionRect(naniButtonTransform, 2);
    playNaniInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    auto lazerButtonTransform = playButtonTransform;
    lazerButtonTransform.position.y += (1080 / 3);
    playLazerButton = runner.getRenderer()->createBasicFillRect(lazerButtonTransform, 3,
                                                                NovelRT::Graphics::RGBAColour(255, 0, 0, 255));
    auto playLazerTextTransform = lazerButtonTransform;
    playLazerTextTransform.position.x -= 50;
    playLazerTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    playLazerText =
        runner.getRenderer()->createTextRect(playLazerTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playLazerText->setText("Pew");
    playLazerInteraction = runner.getInteractionService()->createBasicInteractionRect(lazerButtonTransform, 2);
    playLazerInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

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
    deleteState.state = EmitterState::Done;
    scheduler.GetComponentCache().RegisterComponentType(deleteState);

    // Setup of entities and components
    std::string waltzPath = (soundsDirPath / "waltz.ogg").string();
    std::string naniPath = (soundsDirPath / "nani.ogg").string();
    std::string lazerPath = (soundsDirPath / "lazer.ogg").string();
    std::string goatPath = (soundsDirPath / "goat.ogg").string();
    auto waltzHandle = audioSystem->CreateAudio(waltzPath, true);
    auto naniHandle = audioSystem->CreateAudio(naniPath, false);
    auto lazerHandle = audioSystem->CreateAudio(lazerPath, false);
    auto goatHandle = audioSystem->CreateAudio(goatPath, false);
    AudioEmitterComponent waltzComponent =
        AudioEmitterComponent{waltzHandle, true, -1, NovelRT::Maths::GeoVector2F::zero(), 0.75f, EmitterState::ToPlay};
    // Creating two components to update the music component properly.
    AudioEmitterComponent pauseComponent = waltzComponent;
    pauseComponent.state = EmitterState::ToPause;
    AudioEmitterComponent resumeComponent = waltzComponent;
    resumeComponent.state = EmitterState::ToResume;
    // Now the sound components
    AudioEmitterComponent nani =
        AudioEmitterComponent{naniHandle, false, 0, NovelRT::Maths::GeoVector2F::zero(), 0.75f, EmitterState::Stopped};
    AudioEmitterComponent lazer = nani;
    AudioEmitterComponent goat = nani;
    lazer.handle = lazerHandle;
    goat.handle = goatHandle;
    goat.volume = 1.0f; // o no
    // TODO - separate state from emitter so this is not so bad.
    AudioEmitterComponent naniPlay = nani;
    naniPlay.state = EmitterState::ToPlay;
    AudioEmitterComponent lazerPlay = lazer;
    lazerPlay.state = EmitterState::ToPlay;
    AudioEmitterComponent goatPlay = goat;
    goatPlay.state = EmitterState::ToPlay;

    // Setup of entities and components
    auto entities = NovelRT::Ecs::EntityCache(4);
    scheduler.GetEntityCache() = entities;
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
        0, 0, waltzComponent);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 1,
                                                                                                             nani);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 2,
                                                                                                             lazer);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 3,
                                                                                                             goat);

    playMusicInteraction->Interacted += [&] {
        paused = !paused;
        if (paused)
        {
            scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
                0, 0, pauseComponent);
            console.logDebugLine("Pausing!");
        }
        else
        {
            scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
                0, 0, resumeComponent);
            console.logDebugLine("Resuming!");
        }
    };

    playNaniInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 1 - NANI!?");
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
            0, 1, naniPlay);
    };

    playLazerInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 2 - I'ma firin' mah lazar!");
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
            0, 2, lazerPlay);
    };

    playGoatInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 3 - AHHHHHHHHHHHHHHHHHHHHHHHH");
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(
            0, 3, goatPlay);
    };

    runner.Update += [&](NovelRT::Timing::Timestamp delta) { scheduler.ExecuteIteration(delta); };

    runner.SceneConstructionRequested += [&] {
        playMusicButton->executeObjectBehaviour();
        playNaniButton->executeObjectBehaviour();
        playLazerButton->executeObjectBehaviour();
        playGoatButton->executeObjectBehaviour();
        playMusicText->executeObjectBehaviour();
        playNaniText->executeObjectBehaviour();
        playLazerText->executeObjectBehaviour();
        playGoatText->executeObjectBehaviour();
        playMusicInteraction->executeObjectBehaviour();
        playNaniInteraction->executeObjectBehaviour();
        playLazerInteraction->executeObjectBehaviour();
        playGoatInteraction->executeObjectBehaviour();
    };

    // GASSSSSSSSS GASSSSSSSSSS GASSSSSSSSSSSSSS
    runner.runNovel();

    return 0;
}
