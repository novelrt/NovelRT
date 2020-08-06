#include <NovelRT.h>

using namespace NovelRT::Utilities;
using namespace NovelRT::Lua;

int main() {
  auto executablePath = Misc::getExecutableDirPath();
  auto luaMainPath = (executablePath / "Resources/Scripts/main.lua").string();

  auto runner = LuaRunner(luaMainPath);

  runner.init();
  runner.run();
}
