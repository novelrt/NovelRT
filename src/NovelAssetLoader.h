#ifndef NOVELRT_ASSETLOADER_H
#define NOVELRT_ASSETLOADER_H
#include <string>

namespace NovelRT {
    class NovelAssetLoader {
    public:
        NovelAssetLoader(char* path);

        std::string loadShader(std::string name);

    protected:
        std::string modulePath;
        const std::string& shaderFolder = "\\Shaders\\";

    private:
        std::string getDirectory(std::string path);
        
    };
}

#endif
