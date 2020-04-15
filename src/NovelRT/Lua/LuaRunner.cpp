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

    auto a = _state.new_usertype<NovelRT::NovelRunner>("novel_runner", sol::constructors<NovelRT::NovelRunner(int, std::string)>());
    auto b = _state.new_usertype<NovelRT::Transform>("transform", sol::constructors<NovelRT::Transform(NovelRT::Maths::GeoVector2<float>, int, NovelRT::Maths::GeoVector2<float>)>());
    auto c = _state.new_usertype<NovelRT::Maths::GeoVector2<float>>("geo_vector", sol::constructors<NovelRT::Maths::GeoVector2<float>(int, int)>());
  }

  void LuaRunner::run() {
    _state.script(_fileName);
  }
}
