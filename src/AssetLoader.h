#pragma once
#include <string>

namespace NovelRT {
    class AssetLoader {
    public:
        static void AssetLoader::SetMasterPath(char* path);

        std::string LoadShader(std::string name);

    protected:
        static std::string modulePath;

        std::string shaderFolder = "\\Shaders\\";

    private:
        static std::string GetDirectory(std::string path);
        
    };
}
