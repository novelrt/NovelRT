#include "AssetLoader.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace NovelRT{
  std::string AssetLoader::modulePath;

  void AssetLoader::SetMasterPath(char* path)
  {
    modulePath = GetDirectory(std::string(path));
  }

  std::string AssetLoader::GetDirectory(std::string path)
  {
    //https://stackoverflow.com/questions/8518743/get-directory-from-file-path-c/14631366
    std::string directory;
    const size_t last_slash_idx = path.rfind('\\');
    if (std::string::npos != last_slash_idx)
    {
      directory = path.substr(0, last_slash_idx);
    }
    return directory;
  }

  std::string AssetLoader::LoadShader(std::string name) {
    std::ifstream ShaderStream(modulePath + "\\" + name, std::ios::in);
    std::string toReturn;

    if (ShaderStream.is_open()) {
      std::stringstream sstr;
      sstr << ShaderStream.rdbuf();
      toReturn = sstr.str();
      ShaderStream.close();
    }
    return toReturn;
  }
}
