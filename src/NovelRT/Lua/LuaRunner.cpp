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
    auto transformType = _state.new_usertype<Transform>("Transform",
      sol::constructors<Transform(),
      Transform(const Maths::GeoVector2<float> & position,
        float rotation, const Maths::GeoVector2<float> & scale)>()
      );

    transformType["getAABB"] = sol::property(&Transform::getAABB);
    transformType["getBounds"] = sol::property(&Transform::getBounds);
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
  }

  void LuaRunner::run() {
    auto result = _state.script_file(_fileName);
  }
}
