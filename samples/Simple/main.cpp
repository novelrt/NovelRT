// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

// TODO: Do we really need this anymore? No real reason to run this in WSL these days.
#ifdef WIN32
#define setenv(name, value, overwrite)                                                                                 \
    static_assert(overwrite != 0);                                                                                     \
    _putenv_s(name, value)
#endif

int main(int /*argc*/, char* /*argv*/[])
{
    std::unique_ptr<NovelRT::Graphics::ImageRect> novelChanRect;
    std::unique_ptr<NovelRT::Graphics::TextRect> textRect;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> lineRect;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> inkButton;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> myBasicFillRect;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playAudioButton;
    std::unique_ptr<NovelRT::Graphics::BasicFillRect> playAudioButtonTwoElectricBoogaloo;
    std::unique_ptr<NovelRT::Graphics::TextRect> inkText;
    std::unique_ptr<NovelRT::Graphics::TextRect> playAudioText;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> inkInteractionRect;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> interactionRect;
    std::unique_ptr<NovelRT::Input::BasicInteractionRect> memeInteractionRect;

#undef NOVELRT_INK

#ifdef TEST_ANIM
    std::unique_ptr<NovelRT::Animation::SpriteAnimator> testAnim;
    std::unique_ptr<NovelRT::Graphics::ImageRect> animRect;

    bool shouldBeInIdle = true;
#endif

    std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
    std::filesystem::path resourcesDirPath = executableDirPath / "Resources";

    std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
    std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
    std::filesystem::path scriptsDirPath = resourcesDirPath / "Scripts";
    std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";

    // setenv("DISPLAY", "localhost:0", true);

    auto runner = NovelRT::NovelRunner(0, "NovelRTTest", NovelRT::Windowing::WindowMode::Windowed);
    auto console = NovelRT::LoggingService(NovelRT::Utilities::Misc::CONSOLE_LOG_APP);
    auto audio = runner.getAudioService();
    audio->initializeAudio();
    auto bgm = audio->loadMusic((soundsDirPath / "marisa.ogg").string());
    auto jojo = audio->loadSound((soundsDirPath / "caution.wav").string());

#ifdef TEST_ANIM
    auto movingState = std::make_shared<NovelRT::Animation::SpriteAnimatorState>();
    auto idleState = std::make_shared<NovelRT::Animation::SpriteAnimatorState>();
    idleState->shouldLoop() = true;
    auto idleFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

    for (int32_t i = 0; i < 10; i++)
    {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.duration() = NovelRT::Timing::Timestamp::fromSeconds(0.1f);
        frame.texture() =
            runner.getRenderer()->getTexture((imagesDirPath / "idle" / ("0-" + std::to_string(i) + ".png")).string());
        idleFrames.push_back(frame);
    }

    idleFrames.back().FrameExit += [&shouldBeInIdle] { shouldBeInIdle = false; };

    idleState->insertNewState(movingState,
                              std::vector<std::function<bool()>>{[&shouldBeInIdle] { return !shouldBeInIdle; }});

    idleState->frames() = idleFrames;

    movingState->shouldLoop() = true;
    movingState->insertNewState(idleState,
                                std::vector<std::function<bool()>>{[&shouldBeInIdle] { return shouldBeInIdle; }});

    auto movingFrames = std::vector<NovelRT::Animation::SpriteAnimatorFrame>();

    for (int32_t i = 0; i < 5; i++)
    {
        auto frame = NovelRT::Animation::SpriteAnimatorFrame();
        frame.duration() = NovelRT::Timing::Timestamp::fromSeconds(0.1f);
        frame.texture() = runner.getRenderer()->getTexture(
            (imagesDirPath / "right" / ("100-" + std::to_string(i) + ".png")).string());
        movingFrames.push_back(frame);
    }

    movingFrames.back().FrameExit += [&shouldBeInIdle] { shouldBeInIdle = true; };

    movingState->frames() = movingFrames;

    auto animTransform =
        NovelRT::Transform(NovelRT::Maths::GeoVector2(1500, 900), 2, NovelRT::Maths::GeoVector2(95 * 2, 98 * 2));
    animRect =
        runner.getRenderer()->createImageRect(animTransform, 3, NovelRT::Graphics::RGBAColour(255, 255, 255, 255));
    testAnim = std::make_unique<NovelRT::Animation::SpriteAnimator>(&runner, animRect.get());
    testAnim->insertNewState(idleState);

#endif

    auto novelChanTransform =
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(1920 / 2, 1080 / 2), 2, NovelRT::Maths::GeoVector2F(762, 881));

    novelChanRect =
        runner.getRenderer()->createImageRect(novelChanTransform, 0, (imagesDirPath / "novel-chan.png").string(),
                                              NovelRT::Graphics::RGBAColour(255, 0, 255, 255));

    auto rubyGnomerTextTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x + 400, novelChanTransform.position.y), 0,
        NovelRT::Maths::GeoVector2F(1.0f, 1.0f));

    textRect =
        runner.getRenderer()->createTextRect(rubyGnomerTextTransform, 2, NovelRT::Graphics::RGBAColour(0, 255, 0, 255),
                                             70, (fontsDirPath / "Gayathri-Regular.ttf").string());
    textRect->setText("RubyGnomer");

    auto lineTransform =
        NovelRT::Transform(rubyGnomerTextTransform.position, 0, NovelRT::Maths::GeoVector2F(1000.0f, 2.0f));

    lineRect =
        runner.getRenderer()->createBasicFillRect(lineTransform, 1, NovelRT::Graphics::RGBAColour(255, 0, 0, 255));

    auto myTransform =
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(1, 1), 0.0f, NovelRT::Maths::GeoVector2F(200, 300));
    myBasicFillRect =
        runner.getRenderer()->createBasicFillRect(myTransform, 1, NovelRT::Graphics::RGBAColour(255, 0, 0, 255));

    auto playButtonTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x - 500, novelChanTransform.position.y), 0,
        NovelRT::Maths::GeoVector2F(200, 200));
    playAudioButton =
        runner.getRenderer()->createBasicFillRect(playButtonTransform, 3, NovelRT::Graphics::RGBAColour(255, 0, 0, 70));
    auto playAudioTextTransform = playButtonTransform;
    playAudioTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    auto vec = playButtonTransform.position;
    vec.x = playButtonTransform.position.x - 75;
    playAudioTextTransform.position = vec;
    playAudioText =
        runner.getRenderer()->createTextRect(playAudioTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playAudioText->setText("Play Audio");

    auto theRealMvpTransform = playButtonTransform;
    auto whatever = playButtonTransform.position;
    whatever.x = whatever.x + 50;
    theRealMvpTransform.position = whatever;

    memeInteractionRect = runner.getInteractionService()->createBasicInteractionRect(theRealMvpTransform, -1);

    playAudioButtonTwoElectricBoogaloo =
        runner.getRenderer()->createBasicFillRect(theRealMvpTransform, 2, NovelRT::Graphics::RGBAColour(0, 255, 0, 70));

#ifdef NOVELRT_INK
    auto inkButtonTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x - 500, novelChanTransform.position.y - 200), 0,
        NovelRT::Maths::GeoVector2F(200, 200));
    inkButton = runner.getRenderer()->createBasicFillRect(inkButtonTransform, 3,
                                                          NovelRT::Graphics::RGBAColour(255, 0, 255, 255));
    auto inkTextTransform = inkButtonTransform;
    inkTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    auto inkTextTransformPosition = inkButtonTransform.position;
    inkTextTransformPosition.x = inkButtonTransform.position.x - 75;
    inkTextTransform.position = inkTextTransformPosition;
    inkText = runner.getRenderer()->createTextRect(inkTextTransform, 1, NovelRT::Graphics::RGBAColour(0, 0, 0, 255), 36,
                                                   (fontsDirPath / "Gayathri-Regular.ttf").string());
    inkText->setText("Ink!");
    inkInteractionRect = runner.getInteractionService()->createBasicInteractionRect(inkButtonTransform, -1);
    inkInteractionRect->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;
#endif

    runner.getDebugService()->setIsFpsCounterVisible(true);

    runner.Update += [&](NovelRT::Timing::Timestamp delta) {
        const float rotationAmount = 45.0f;

        auto rotation = novelChanRect->transform().rotation;
        rotation += rotationAmount * delta.getSecondsFloat();
        novelChanRect->transform().rotation = rotation;

        if (rotation > 360.0f)
        {
            rotation -= 360.0f;
        }

        novelChanRect->transform().rotation = rotation;

        if (runner.getInteractionService()->getKeyState(NovelRT::Input::KeyCode::W) ==
            NovelRT::Input::KeyState::KeyDown)
        {
            console.logInfoLine("W is not idle!");
            console.logInfoLine(
                std::to_string(
                    runner.getInteractionService()->getKeyState(NovelRT::Input::KeyCode::W).getChangeCount()) +
                " key transitions!");
        }
        else if (runner.getInteractionService()->getKeyState(NovelRT::Input::KeyCode::W) ==
                 NovelRT::Input::KeyState::KeyUp)
        {
            console.logInfoLine("W Key came up!");
        }
    };

    interactionRect = runner.getInteractionService()->createBasicInteractionRect(playButtonTransform, 2);
    memeInteractionRect->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;
    interactionRect->subscribedKey() = NovelRT::Input::KeyCode::RightMouseButton;

    auto loggingLevel = NovelRT::LogLevel::Debug;

    memeInteractionRect->Interacted += [&] {
        console.logDebug("WAHEYYY");
        audio->playSound(jojo, 0);
    };

    interactionRect->Interacted += [&] {
        console.log("Test button!", loggingLevel);

#ifdef TEST_ANIM
        switch (testAnim->getCurrentPlayState())
        {
            case NovelRT::Animation::AnimatorPlayState::Playing:
                testAnim->stop();
                break;
            case NovelRT::Animation::AnimatorPlayState::Stopped:
                testAnim->play();
                break;
        }
#endif
    };

    runner.SceneConstructionRequested += [&] {
        playAudioButton->executeObjectBehaviour();
        playAudioButtonTwoElectricBoogaloo->executeObjectBehaviour();
        playAudioText->executeObjectBehaviour();

#ifdef NOVELRT_INK
        inkButton->executeObjectBehaviour();
        inkText->executeObjectBehaviour();
#endif

        memeInteractionRect->executeObjectBehaviour();
        interactionRect->executeObjectBehaviour();
#ifdef NOVELRT_INK
        inkInteractionRect->executeObjectBehaviour();
#endif

        novelChanRect->executeObjectBehaviour();

#ifdef TEST_ANIM
        animRect->executeObjectBehaviour();
#endif

        textRect->executeObjectBehaviour();
        myBasicFillRect->executeObjectBehaviour();
        lineRect->executeObjectBehaviour();
    };

#ifdef NOVELRT_INK
    auto dotnetRuntimeService = runner.getDotNetRuntimeService();
    dotnetRuntimeService->initialise();

    auto inkService = dotnetRuntimeService->getInkService();
    inkService->initialise();

    std::shared_ptr<NovelRT::Ink::Story> story;

    std::ifstream storyJsonStream(scriptsDirPath / "story.json", std::ios::in);
    if (storyJsonStream.is_open())
    {
        std::stringstream sstr;
        sstr << storyJsonStream.rdbuf();

        auto storyJsonString = sstr.str();
        storyJsonStream.close();

        story = inkService->createStory(storyJsonString.c_str());
        story->ResetState(); // Force initialization to happen
    }

    inkInteractionRect->Interacted += [&] {
        if (!story->CanContinue())
        {
            story->ResetState();
        }

        auto result = story->Continue();
        console.logDebug(result);
        dotnetRuntimeService->freeString(result);
    };
#endif
    audio->playMusic(bgm, -1);
    runner.runNovel();

    return 0;
}
