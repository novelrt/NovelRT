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

    // NovelRunner
    auto novelRunnerType = _state.new_usertype<NovelRunner>("NovelRunner",
      sol::constructors<NovelRunner(int), NovelRunner(int, const std::string&), NovelRunner(int, const std::string&, uint32_t)>());

    novelRunnerType["runNovel"] = &NovelRunner::runNovel;
    novelRunnerType["getRenderer"] = sol::property(&NovelRunner::getRenderer);
    novelRunnerType["getInteractionService"] = sol::property(&NovelRunner::getInteractionService);
    novelRunnerType["getAudioService"] = sol::property(&NovelRunner::getAudioService);
    novelRunnerType["getDebugService"] = sol::property(&NovelRunner::getDebugService);
    novelRunnerType["getDotNetRuntimeService"] = sol::property(&NovelRunner::getDotNetRuntimeService);
    novelRunnerType["getWindowingService"] = sol::property(&NovelRunner::getWindowingService);
  }

  void LuaRunner::run() {
    auto result = _state.script_file(_fileName);
  }
}
