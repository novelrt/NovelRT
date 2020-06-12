// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

using namespace sol;

namespace NovelRT::Lua {
  LuaRunner::LuaRunner(const std::string& fileName) noexcept {
    _fileName = fileName;
  }

  void LuaRunner::init() {
    _state = sol::state();
    _state.open_libraries(lib::base, lib::bit32, lib::coroutine,
      lib::debug, lib::io, lib::math, lib::os,
      lib::package, lib::string, lib::table, lib::utf8);

    auto globalTable = _state.create_table("novelrt");

    _state["novelrt"] = globalTable;

#pragma region NovelRT::
    // Atom
    auto atomType = globalTable.new_usertype<Atom>("Atom", sol::constructors<Atom(), Atom(uintptr_t)>());

    atomType["getNextEventHandlerId"] = &Atom::getNextEventHandlerId;
    atomType["getNextFontSetId"] = &Atom::getNextFontSetId;
    atomType["getNextTextureId"] = &Atom::getNextTextureId;

    // DebugService
    auto debugServiceType = globalTable.new_usertype<DebugService>("DebugService", sol::constructors<DebugService(NovelRunner* const)>());
    debugServiceType["fpsCounterVisible"] = sol::property(
      static_cast<bool (DebugService::*)() const>(&DebugService::getIsFpsCounterVisible),
      static_cast<void (DebugService::*)(bool)>(&DebugService::setIsFpsCounterVisible)
      );

    debugServiceType["framesPerSecond"] = sol::property(
      static_cast<uint32_t(DebugService::*)() const>(&DebugService::getFramesPerSecond),
      static_cast<void (DebugService::*)(uint32_t)>(&DebugService::setFramesPerSecond)
      );


    // LoggingService
    auto loggingServiceType = globalTable.new_usertype<LoggingService>("LoggingService",
      sol::constructors<LoggingService(), LoggingService(const std::string&), LoggingService(const std::string&, LogLevel)>());

    loggingServiceType["log"] = &LoggingService::log;
    loggingServiceType["logInfoLine"] = &LoggingService::logInfoLine;
    loggingServiceType["logErrorLine"] = &LoggingService::logErrorLine;
    loggingServiceType["logWarningLine"] = &LoggingService::logWarningLine;
    loggingServiceType["logDebugLine"] = &LoggingService::logDebugLine;
    loggingServiceType["logInternal"] = &LoggingService::logInternal;
    loggingServiceType["setLogLevel"] = &LoggingService::setLogLevel;

    // TODO: should I include throwIfNullPtr/NotZero?
    // TODO: figure out how to specify template types for logInfo/Error/Warning/Debug

    // LogLevel

    globalTable.new_enum<LogLevel>("LogLevel", {
      { "Debug", LogLevel::Debug },
      { "Info", LogLevel::Info },
      { "Warn", LogLevel::Warn },
      { "Error", LogLevel::Err },
      { "Off", LogLevel::Off }
      });


    // NovelRunner
    auto novelRunnerType = globalTable.new_usertype<NovelRunner>("NovelRunner",
      sol::constructors<NovelRunner(int), NovelRunner(int, const std::string&), NovelRunner(int, const std::string&, uint32_t)>()
      );

    novelRunnerType["runNovel"] = &NovelRunner::runNovel;
    novelRunnerType["getRenderer"] = sol::property(&NovelRunner::getRenderer);
    novelRunnerType["getInteractionService"] = sol::property(&NovelRunner::getInteractionService);
    novelRunnerType["getAudioService"] = sol::property(&NovelRunner::getAudioService);
    novelRunnerType["getDebugService"] = sol::property(&NovelRunner::getDebugService);
    novelRunnerType["getDotNetRuntimeService"] = sol::property(&NovelRunner::getDotNetRuntimeService);
    novelRunnerType["getWindowingService"] = sol::property(&NovelRunner::getWindowingService);

    // Transform
    auto transformType = globalTable.new_usertype<Transform>("Transform",
      sol::constructors<Transform(),
      Transform(const Maths::GeoVector2<float> & position,
        float rotation, const Maths::GeoVector2<float> & scale)>()
      );

    transformType["AABB"] = sol::property(&Transform::getAABB);
    transformType["bounds"] = sol::property(&Transform::getBounds);
    transformType["position"] = sol::property(
      static_cast<const Maths::GeoVector2<float> & (Transform::*)() const>(&Transform::position),
      static_cast<Maths::GeoVector2<float>& (Transform::*)()>(&Transform::position)
      );

    transformType["rotation"] = sol::property(
      static_cast<const float& (Transform::*)() const>(&Transform::rotation),
      static_cast<float& (Transform::*)()>(&Transform::rotation)
      );

    transformType["scale"] = sol::property(
      static_cast<const Maths::GeoVector2<float> & (Transform::*)() const>(&Transform::scale),
      static_cast<Maths::GeoVector2<float>& (Transform::*)()>(&Transform::scale)
      );

    // WorldObject is left out, because it is an abstract class and isn't consumed or returned in any parts of the api.

#pragma endregion

#pragma region NovelRT::Animation

    //AnimatorPlayState

    globalTable.new_enum<Animation::AnimatorPlayState>("AnimatorPlayState", {
      { "Paused", Animation::AnimatorPlayState::Paused },
      { "Playing", Animation::AnimatorPlayState::Playing },
      { "Stopped", Animation::AnimatorPlayState::Stopped }
      });

    //SpriteAnimator

    auto spriteAnimatorType = globalTable.new_usertype<Animation::SpriteAnimator>("SpriteAnimator",
      sol::constructors<Animation::SpriteAnimator(NovelRunner*, Graphics::ImageRect*)>());

    spriteAnimatorType["play"] = &Animation::SpriteAnimator::play;
    spriteAnimatorType["pause"] = &Animation::SpriteAnimator::pause;
    spriteAnimatorType["stop"] = &Animation::SpriteAnimator::stop;
    spriteAnimatorType["currentPlayState"] = sol::property(&Animation::SpriteAnimator::getCurrentPlayState);
    spriteAnimatorType["insertNewState"] = &Animation::SpriteAnimator::insertNewState;

    //SpriteAnimatorFrame

    auto spriteAnimatorFrameType = globalTable.new_usertype<Animation::SpriteAnimatorFrame>("SpriteAnimatorFrame",
      sol::constructors<Animation::SpriteAnimatorFrame()>());

    spriteAnimatorFrameType["frameEnter"] = &Animation::SpriteAnimatorFrame::FrameEnter;
    spriteAnimatorFrameType["frameExit"] = &Animation::SpriteAnimatorFrame::FrameExit;

    spriteAnimatorFrameType["texture"] = sol::property(
      static_cast<const std::shared_ptr<Graphics::Texture> & (Animation::SpriteAnimatorFrame::*)() const>(&Animation::SpriteAnimatorFrame::texture),
      static_cast<std::shared_ptr<Graphics::Texture> & (Animation::SpriteAnimatorFrame::*)()>(&Animation::SpriteAnimatorFrame::texture)
      );

    spriteAnimatorFrameType["duration"] = sol::property(
      static_cast<const Timing::Timestamp & (Animation::SpriteAnimatorFrame::*)() const>(&Animation::SpriteAnimatorFrame::duration),
      static_cast<Timing::Timestamp & (Animation::SpriteAnimatorFrame::*)()>(&Animation::SpriteAnimatorFrame::duration)
      );

    //SpriteAnimatorState

    auto spriteAnimatorStateType = globalTable.new_usertype<Animation::SpriteAnimatorState>("SpriteAnimatorState");

    spriteAnimatorStateType["insertNewState"] = &Animation::SpriteAnimatorState::insertNewState;
    spriteAnimatorStateType["removeStateAtIndex"] = &Animation::SpriteAnimatorState::removeStateAtIndex;
    spriteAnimatorStateType["shouldLoop"] = sol::property(
      static_cast<const bool& (Animation::SpriteAnimatorState::*)() const>(&Animation::SpriteAnimatorState::shouldLoop),
      static_cast<bool& (Animation::SpriteAnimatorState::*)()>(&Animation::SpriteAnimatorState::shouldLoop)
      );
    spriteAnimatorStateType["frames"] = sol::property(
      static_cast<const std::vector<Animation::SpriteAnimatorFrame> & (Animation::SpriteAnimatorState::*)() const>(&Animation::SpriteAnimatorState::frames),
      static_cast<std::vector<Animation::SpriteAnimatorFrame> & (Animation::SpriteAnimatorState::*)()>(&Animation::SpriteAnimatorState::frames)
      );
    spriteAnimatorStateType["tryFindValidTransition"] = &Animation::SpriteAnimatorState::tryFindValidTransition;

#pragma endregion

#pragma region NovelRT::Audio
#pragma endregion

#pragma region NovelRT::DotNet
#pragma endregion

#pragma region NovelRT::Graphics
    //ImageRect
    auto imageRectType = globalTable.new_usertype<Graphics::ImageRect>("ImageRect",
      sol::constructors<Graphics::ImageRect(const Transform&, int, Graphics::ShaderProgram, std::weak_ptr<Graphics::Camera>, const Graphics::RGBAConfig&),
      Graphics::ImageRect(const Transform&, int, Graphics::ShaderProgram, std::weak_ptr<Graphics::Camera>, std::shared_ptr<Graphics::Texture>, const Graphics::RGBAConfig&)>()
      );

    imageRectType["texture"] = sol::property(static_cast<const std::shared_ptr<Graphics::Texture>& (Graphics::ImageRect::*)() const>(&Graphics::ImageRect::texture));
    imageRectType["colourTint"] = sol::property(static_cast<const Graphics::RGBAConfig& (Graphics::ImageRect::*)() const>(&Graphics::ImageRect::colourTint));



#pragma endregion

#pragma region NovelRT::Input
#pragma endregion

#pragma region NovelRT::Maths
#pragma endregion

#pragma region NovelRT::Timing
#pragma endregion

#pragma region NovelRT::Utilities
#pragma endregion

#pragma region NovelRT::Windowing
#pragma endregion

  }

  void LuaRunner::run() {
    try {
      auto result = _state.safe_script_file(_fileName);
    }
    catch (const sol::error& err) {
      std::cout << "An error occurred from within sol: " << err.what() << std::endl;
    }
    
  }
}
