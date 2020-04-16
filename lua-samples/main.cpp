// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

int main(int /*argc*/, char* /*argv*/[])
{
  std::filesystem::path executableDirPath = NovelRT::Utilities::Misc::getExecutableDirPath();
  std::filesystem::path resourcesDirPath = executableDirPath / "Resources";

  std::filesystem::path fontsDirPath = resourcesDirPath / "Fonts";
  std::filesystem::path imagesDirPath = resourcesDirPath / "Images";
  std::filesystem::path scriptsDirPath = resourcesDirPath / "Scripts";
  std::filesystem::path soundsDirPath = resourcesDirPath / "Sounds";


  auto luaRunner = NovelRT::Lua::LuaRunner((scriptsDirPath / "main.lua").string());
  luaRunner.init();
  luaRunner.run();
  return 0;
}
