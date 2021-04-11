// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <NovelRT/Physics/Box2d/Components/PhysicsBody.h>
#include <NovelRT/Physics/Box2d/Components/PhysicsWorld.h>
#include <NovelRT/Physics/Box2d/Components/TestTransform.h>
#include <NovelRT/Physics/Box2d/Systems/Box2dSystem.h>

// TODO: What do I do with these?
extern "C"
{
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

static int average(lua_State* luaState)
{
    int n = lua_gettop(luaState);
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += lua_tonumber(luaState, i);
    }
    lua_pushnumber(luaState, sum / n);
    lua_pushnumber(luaState, sum);
    return 2;
}

// TODO: Do we really need this anymore? No real reason to run this in WSL these days.
#ifdef WIN32
#define setenv(name, value, overwrite)                                                                                 \
    static_assert(overwrite != 0);                                                                                     \
    _putenv_s(name, value)
#endif

int main(int /*argc*/, char* /*argv*/[])
{

    // create world
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    NovelRT::Ecs::SystemScheduler scheduler(0);

    NovelRT::Physics::Box2d::Box2dSystem::RegisterSystem(&scheduler);

    scheduler.GetComponentCache().RegisterComponentType<NovelRT::Physics::Box2d::PhysicsBody>(
        NovelRT::Physics::Box2d::PhysicsBody::DeletedBodyState);
    scheduler.GetComponentCache().RegisterComponentType<NovelRT::Physics::Box2d::PhysicsWorld>(
        NovelRT::Physics::Box2d::PhysicsWorld::DeletedWorld);
    scheduler.GetComponentCache().RegisterComponentType<NovelRT::Physics::Box2d::TestTransform>(
        NovelRT::Physics::Box2d::TestTransform::DeletedTransform);
    scheduler.SpinThreads();

    auto worldEntityId = NovelRT::Atom::getNextEntityId();
    auto pWorld = NovelRT::Physics::Box2d::Box2dSystem::AddWorld(&scheduler, worldEntityId, &world, 1.0f / 60);

    // define the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(200.0f, 10.0f);

    // create the body based on the definition
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0);

    b2Vec2 b2VecTest(1, 2);
    NovelRT::Maths::GeoVector2F geoVec = *reinterpret_cast<NovelRT::Maths::GeoVector2F*>(&b2VecTest);

    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position = b2Vec2(200, 100);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10, 10);

    b2FixtureDef boxDef;
    boxDef.shape = &dynamicBox;
    boxDef.density = 1;
    boxDef.friction = 0.3f;

    body->CreateFixture(&boxDef);

    lua_State* L;

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
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "average", average);
    luaL_dofile(L, (scriptsDirPath / "avg.lua").string().c_str());
    lua_close(L);

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
        runner.getRenderer()->createImageRect(animTransform, 3, NovelRT::Graphics::RGBAConfig(255, 255, 255, 255));
    testAnim = std::make_unique<NovelRT::Animation::SpriteAnimator>(&runner, animRect.get());
    testAnim->insertNewState(idleState);

#endif

    auto novelChanTransform =
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(1920 / 2, 1080 / 2), 2, NovelRT::Maths::GeoVector2F(762, 881));

    novelChanRect =
        runner.getRenderer()->createImageRect(novelChanTransform, 3, (imagesDirPath / "novel-chan.png").string(),
                                              NovelRT::Graphics::RGBAConfig(255, 0, 255, 255));

    auto rubyGnomerTextTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x + 400, novelChanTransform.position.y), 0,
        NovelRT::Maths::GeoVector2F(1.0f, 1.0f));

    textRect =
        runner.getRenderer()->createTextRect(rubyGnomerTextTransform, 2, NovelRT::Graphics::RGBAConfig(0, 255, 0, 255),
                                             70, (fontsDirPath / "Gayathri-Regular.ttf").string());
    textRect->setText("RubyGnomer");

    auto groundRect = runner.getRenderer()->createBasicFillRect(
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(200.0f, 10.0f), 0, NovelRT::Maths::GeoVector2F(100, 20)), 2,
        NovelRT::Graphics::RGBAConfig(255, 248, 220, 255));
    auto boxRect = runner.getRenderer()->createBasicFillRect(
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(0.0f, 4.0f), 0, NovelRT::Maths::GeoVector2F(20, 20)), 2,
        NovelRT::Graphics::RGBAConfig(30, 248, 220, 255));

    auto lineTransform =
        NovelRT::Transform(rubyGnomerTextTransform.position, 0, NovelRT::Maths::GeoVector2F(1000.0f, 2.0f));

    lineRect =
        runner.getRenderer()->createBasicFillRect(lineTransform, 1, NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));

    auto myTransform =
        NovelRT::Transform(NovelRT::Maths::GeoVector2F(1, 1), 0.0f, NovelRT::Maths::GeoVector2F(200, 300));
    myBasicFillRect =
        runner.getRenderer()->createBasicFillRect(myTransform, 1, NovelRT::Graphics::RGBAConfig(255, 0, 0, 255));

    auto playButtonTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x - 500, novelChanTransform.position.y), 0,
        NovelRT::Maths::GeoVector2F(200, 200));
    playAudioButton =
        runner.getRenderer()->createBasicFillRect(playButtonTransform, 3, NovelRT::Graphics::RGBAConfig(255, 0, 0, 70));
    auto playAudioTextTransform = playButtonTransform;
    playAudioTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    auto vec = playButtonTransform.position;
    vec.x = playButtonTransform.position.x - 75;
    playAudioTextTransform.position = vec;
    playAudioText =
        runner.getRenderer()->createTextRect(playAudioTextTransform, 1, NovelRT::Graphics::RGBAConfig(0, 0, 0, 255), 36,
                                             (fontsDirPath / "Gayathri-Regular.ttf").string());
    playAudioText->setText("Play Audio");

    auto theRealMvpTransform = playButtonTransform;
    auto whatever = playButtonTransform.position;
    whatever.x = whatever.x + 50;
    theRealMvpTransform.position = whatever;

    memeInteractionRect = runner.getInteractionService()->createBasicInteractionRect(theRealMvpTransform, -1);

    playAudioButtonTwoElectricBoogaloo =
        runner.getRenderer()->createBasicFillRect(theRealMvpTransform, 2, NovelRT::Graphics::RGBAConfig(0, 255, 0, 70));

    auto inkButtonTransform = NovelRT::Transform(
        NovelRT::Maths::GeoVector2F(novelChanTransform.position.x - 500, novelChanTransform.position.y - 200), 0,
        NovelRT::Maths::GeoVector2F(200, 200));
    inkButton = runner.getRenderer()->createBasicFillRect(inkButtonTransform, 3,
                                                          NovelRT::Graphics::RGBAConfig(255, 0, 255, 255));
    auto inkTextTransform = inkButtonTransform;
    inkTextTransform.scale = NovelRT::Maths::GeoVector2F(1.0f, 1.0f);
    auto inkTextTransformPosition = inkButtonTransform.position;
    inkTextTransformPosition.x = inkButtonTransform.position.x - 75;
    inkTextTransform.position = inkTextTransformPosition;
    inkText = runner.getRenderer()->createTextRect(inkTextTransform, 1, NovelRT::Graphics::RGBAConfig(0, 0, 0, 255), 36,
                                                   (fontsDirPath / "Gayathri-Regular.ttf").string());
    inkText->setText("Ink!");
    inkInteractionRect = runner.getInteractionService()->createBasicInteractionRect(inkButtonTransform, -1);
    inkInteractionRect->subscribedKey() = NovelRT::Input::KeyCode::LeftMouseButton;

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

        inkButton->executeObjectBehaviour();
        inkText->executeObjectBehaviour();

        memeInteractionRect->executeObjectBehaviour();
        interactionRect->executeObjectBehaviour();
        inkInteractionRect->executeObjectBehaviour();

        novelChanRect->executeObjectBehaviour();

#ifdef TEST_ANIM
        animRect->executeObjectBehaviour();
#endif

        textRect->executeObjectBehaviour();
        myBasicFillRect->executeObjectBehaviour();
        lineRect->executeObjectBehaviour();

        groundRect->executeObjectBehaviour();
        boxRect->executeObjectBehaviour();
    };

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

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    auto entityId = NovelRT::Atom::getNextEntityId();
    auto t = boxRect->transform();
    auto tt = NovelRT::Physics::Box2d::TestTransform{t.position, t.rotation};

    scheduler.GetComponentCache()
        .GetComponentBuffer<NovelRT::Physics::Box2d::TestTransform>()
        .PushComponentUpdateInstruction(0, entityId, tt);

    NovelRT::Physics::Box2d::Box2dSystem::AddBody(&world, &groundBodyDef)->CreateFixture(&groundBox, 0);
    NovelRT::Physics::Box2d::Box2dSystem::AddBodyComponent(&scheduler, &world, entityId, &bodyDef, &boxDef);

    // system.AddBody(&groundBodyDef)->CreateFixture(&groundBox,0);
    // system.AddEntityBody(&scheduler,entityId,&bodyDef).body->CreateFixture(&boxDef);

    runner.Update += [&](NovelRT::Timing::Timestamp delta) {
#if false
        world.Step(delta.getSecondsFloat(), velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        boxRect->transform().position = *reinterpret_cast<NovelRT::Maths::GeoVector2F*>(&position);
        float angle = body->GetAngle();
        char message[50];
        sprintf(message,"%4.2f %4.2f %4.2f\n",position.x, position.y, angle);
        
        console.log(message, NovelRT::LogLevel::Debug);
#else
        scheduler.ExecuteIteration(delta);

        auto ttBuffer = scheduler.GetComponentCache().GetComponentBuffer<NovelRT::Physics::Box2d::TestTransform>();
        auto ttComponent = ttBuffer.GetComponent(entityId);

        auto pwBuffer = scheduler.GetComponentCache().GetComponentBuffer<NovelRT::Physics::Box2d::PhysicsWorld>();
        auto pwComponent = pwBuffer.GetComponent(worldEntityId);

        auto testTransform = ttComponent;
        boxRect->transform().position = testTransform.position;
        boxRect->transform().rotation = testTransform.rotation;
#endif
    };

    audio->playMusic(bgm, -1);
    runner.runNovel();

    return 0;
}
