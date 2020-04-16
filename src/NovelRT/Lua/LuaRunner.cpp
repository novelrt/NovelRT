#include <string>
#include <NovelRT.h>
using namespace sol;

namespace NovelRT::Lua {
  LuaRunner::LuaRunner(std::string fileName) {
    _fileName = fileName;
  }

  void LuaRunner::init() {
    _state = sol::state();
    _state.open_libraries(lib::base, lib::bit32, lib::coroutine,
      lib::debug, lib::io, lib::math, lib::os,
      lib::package, lib::string, lib::table, lib::utf8);

    auto globalTable = _state.create_table("novelrt");

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
      sol::constructors<LoggingService(), LoggingService(const std::string & core), LoggingService(const std::string * core, LogLevel)>());

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

    _state["novelrt"] = globalTable;
  }

  void LuaRunner::run() {
    auto result = _state.script_file(_fileName);
  }
}
