#include "NovelAssetLoader.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
//TODO: This comment is just to trigger a rebuild. Plz remove kthx.
namespace NovelRT{

  NovelAssetLoader::NovelAssetLoader(char* path)
  {
    modulePath = getDirectory(std::string(path));
  }

  FT_Face NovelAssetLoader::loadFont(std::string path, FT_Library* ftLoader)
  {
    std::string filepath = modulePath + fontsFolder + path;
    if (FT_Init_FreeType(ftLoader)) {
      std::cerr << "ERROR: Failed to initialise Freetype." << std::endl;
    }
    FT_Face face;
    if (FT_New_Face(*ftLoader, filepath.c_str(), 0, &face))
      std::cout << "ERROR: Failed to load font " << filepath << " via freeType!" << std::endl;

    return face;
  }

  std::string NovelAssetLoader::getDirectory(std::string path)
  {
    //https://stackoverflow.com/questions/8518743/get-directory-from-file-path-c/14631366
    std::string directory;
    const size_t lastSlashIndex = path.rfind('\\');
    if (std::string::npos != lastSlashIndex) directory = path.substr(0, lastSlashIndex);
    return directory;
  }

  std::string NovelAssetLoader::loadShader(std::string name)
  {
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

  SDL_Surface* NovelAssetLoader::loadImage(std::string filename)
  {
    std::string path = modulePath + imagesFolder + filename;
    return IMG_Load(path.c_str());
  }

  Mix_Chunk* NovelAssetLoader::loadAudio(std::string filename)
  {
    return nullptr;
  }

}
