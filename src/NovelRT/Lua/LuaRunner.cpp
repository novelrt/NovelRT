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
      sol::constructors<NovelRunner(int), NovelRunner(int, std::string), NovelRunner(int, int, std::string)>());

    novelRunnerType["runNovel"] = &NovelRunner::runNovel;
    novelRunnerType["getRenderer"] = &NovelRunner::getRenderer;
    novelRunnerType["getInteractionService"] = &NovelRunner::getInteractionService;
    novelRunnerType["getAudioService"] = &NovelRunner::getAudioService;
    novelRunnerType["getDebugService"] = &NovelRunner::getDebugService;
    novelRunnerType["getDotNetRuntimeService"] = &NovelRunner::getDotNetRuntimeService;
    novelRunnerType["getWindowingService"] = &NovelRunner::getWindowingService;

  }

  void LuaRunner::run() {
    auto result = _state.script_file(_fileName);
  }
}
