// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <time.h>

using namespace NovelRT::Ecs::Audio;

int main(int, char*[])
{
    //RNG
    srand (time(NULL));

    // Old resources setup
    std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
    std::filesystem::path resourcesDirPath = executableDirPath / "Resources";
    std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
    std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";

    // Button setup - old way
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playMusicButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> playMusicInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> playMusicText;

    std::unique_ptr<NovelRT::Graphics::BasicFillRect> fadeMusicOutButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> fadeMusicOutInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> fadeMusicOutText;

    std::unique_ptr<NovelRT::Graphics::BasicFillRect> fadeMusicInButton;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> fadeMusicInInteraction;
    std::unique_ptr<NovelRT::Graphics::TextRect> fadeMusicInText;

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
    runner.getDebugService()->setIsFpsCounterVisible(false);
    runner.getRenderer()->setBackgroundColour(NovelRT::Graphics::RGBAColour(103, 128, 159, 255));

    // Creating the UI
    auto playButtonTransform = NovelRT::Transform(NovelRT::Maths::GeoVector2F((1920 / 2), (1080 / 2)), 0,
                                                  NovelRT::Maths::GeoVector2F(200, 200));
//    playMusicButton = runner.getRenderer()->createBasicFillRect(playButtonTransform, 3,
//                                                                NovelRT::Graphics::RGBAColour(rand()%255, rand()%255, rand()%255, 255));
//    auto playMusicTextTransform = playButtonTransform;
//    playMusicTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
//    auto vec = playButtonTransform.position;
//    vec.x = playButtonTransform.position.x - 75;
//    playMusicTextTransform.position = vec;
//    playMusicText =
//        runner.getRenderer()->createTextRect(playMusicTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
//                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
//    playMusicText->setText("Play / Pause");
//    playMusicInteraction = runner.getInteractionService()->createBasicInteractionRect(playButtonTransform, 2);
//    playMusicInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;
    bool paused = false;

    //fade music in button
    auto fadeMusicInTransform = playButtonTransform;
    fadeMusicInTransform.position.x += (1920 / 3);
    fadeMusicInButton = runner.getRenderer()->createBasicFillRect(fadeMusicInTransform, 3,
                                                                NovelRT::Graphics::RGBAColour(rand()%255, rand()%255, rand()%255, 255));
    auto fadeMusicInTextTransform = fadeMusicInTransform;
    fadeMusicInTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    fadeMusicInText =
        runner.getRenderer()->createTextRect(fadeMusicInTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    fadeMusicInText->setText("Fade In");
    fadeMusicInInteraction = runner.getInteractionService()->createBasicInteractionRect(fadeMusicInTransform, 2);
    fadeMusicInInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

    //fade music out button
    auto fadeMusicOutTransform = playButtonTransform;
    fadeMusicOutTransform.position.x -= (1920 / 3);
    fadeMusicOutButton = runner.getRenderer()->createBasicFillRect(fadeMusicOutTransform, 3,
                                                                  NovelRT::Graphics::RGBAColour(rand()%255, rand()%255, rand()%255, 255));
    auto fadeMusicOutTextTransform = fadeMusicOutTransform;
    fadeMusicOutTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    fadeMusicOutText =
        runner.getRenderer()->createTextRect(fadeMusicOutTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    fadeMusicOutText->setText("Fade Out");
    fadeMusicOutInteraction = runner.getInteractionService()->createBasicInteractionRect(fadeMusicOutTransform, 2);
    fadeMusicOutInteraction->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;


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
    scheduler.GetComponentCache().RegisterComponentType(deleteState);
    scheduler.GetComponentCache().RegisterComponentType(AudioEmitterStateComponent{AudioEmitterState::Done});

    // Setup of entities and components
    std::string waltzPath = (soundsDirPath / "waltz.ogg").string();
    std::string lazerPath = (soundsDirPath / "laz0r.ogg").string();
    std::string goatPath = (soundsDirPath / "goat.ogg").string();
    auto waltzHandle = audioSystem->CreateAudio(waltzPath, true);
    auto lazerHandle = audioSystem->CreateAudio(lazerPath, false);
    auto goatHandle = audioSystem->CreateAudio(goatPath, false);
    AudioEmitterComponent waltzComponent =
        AudioEmitterComponent{waltzHandle, true, -1, 0.75f};
    AudioEmitterStateComponent waltzState = AudioEmitterStateComponent{AudioEmitterState::Stopped, 5.0};
    // Now the sound components
    AudioEmitterComponent lazer =
        AudioEmitterComponent{lazerHandle, false, 0, 0.75f};
    AudioEmitterComponent goat = lazer;
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
                                                                                                             lazer);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 1, AudioEmitterStateComponent{AudioEmitterState::Stopped});

    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterComponent>().PushComponentUpdateInstruction(0, 2,
                                                                                                             goat);
    scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
        0, 2, AudioEmitterStateComponent{AudioEmitterState::Stopped});

    playMusicInteraction->Interacted += [&] {
        paused = !paused;
        if (paused)
        {
            scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
                0, 0, AudioEmitterStateComponent{AudioEmitterState::ToPause});
            console.logDebugLine("Pausing!");
        }
        else
        {
            scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
                0, 0, AudioEmitterStateComponent{AudioEmitterState::ToResume});
            console.logDebugLine("Resuming!");
        }
    };

    fadeMusicOutInteraction->Interacted +=  [&] {
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 0, AudioEmitterStateComponent{AudioEmitterState::ToFadeOut, 5.0f, 0.0f});
        console.logDebugLine("Fading music out!");
    };

    fadeMusicInInteraction->Interacted +=  [&] {
        scheduler.GetComponentCache().GetComponentBuffer<AudioEmitterStateComponent>().PushComponentUpdateInstruction(
            0, 0, AudioEmitterStateComponent{AudioEmitterState::ToFadeIn, 5.0f, 0.0f});
        console.logDebugLine("Fading music in!");
    };

    playLazerInteraction->Interacted += [&] {
        console.logInfoLine("Entity Id: 1 - I'ma firin' mah lazar!");
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
        playLazerButton->executeObjectBehaviour();
        playGoatButton->executeObjectBehaviour();
        fadeMusicInText->executeObjectBehaviour();
        fadeMusicOutText->executeObjectBehaviour();
        playLazerText->executeObjectBehaviour();
        playGoatText->executeObjectBehaviour();
        fadeMusicInInteraction->executeObjectBehaviour();
        fadeMusicOutInteraction->executeObjectBehaviour();
        playLazerInteraction->executeObjectBehaviour();
        playGoatInteraction->executeObjectBehaviour();
    };

    // GASSSSSSSSS GASSSSSSSSSS GASSSSSSSSSSSSSS
    runner.runNovel();

    return 0;
}
