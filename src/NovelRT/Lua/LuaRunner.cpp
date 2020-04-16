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

    novelRunnerType["run_novel"] = &NovelRunner::runNovel;
    novelRunnerType["get_renderer"] = &NovelRunner::getRenderer;
    novelRunnerType["get_interaction_service"] = &NovelRunner::getInteractionService;
    novelRunnerType["get_audio_service"] = &NovelRunner::getAudioService;
    novelRunnerType["get_debug_service"] = &NovelRunner::getDebugService;
    novelRunnerType["get_dot_net_runtime_service"] = &NovelRunner::getDotNetRuntimeService;
    novelRunnerType["get_windowing_service"] = &NovelRunner::getWindowingService;

  }

  void LuaRunner::run() {
    auto result = _state.script_file(_fileName);
  }
}
