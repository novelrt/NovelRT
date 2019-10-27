#include "NovelAssetLoader.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace NovelRT{

  NovelAssetLoader::NovelAssetLoader(char* path)
  {
    modulePath = getDirectory(std::string(path));
  }

  std::string NovelAssetLoader::getDirectory(std::string path)
  {
    //https://stackoverflow.com/questions/8518743/get-directory-from-file-path-c/14631366
    std::string directory;
    const size_t lastSlashIndex = path.rfind('\\');
    if (std::string::npos != lastSlashIndex) directory = path.substr(0, lastSlashIndex);
    return directory;
  }

  std::string NovelAssetLoader::loadShader(std::string name) {
    std::ifstream ShaderStream(modulePath + shaderFolder + name, std::ios::in);
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
