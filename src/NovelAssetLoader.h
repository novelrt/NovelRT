#ifndef NOVELRT_ASSETLOADER_H
#define NOVELRT_ASSETLOADER_H
#include <string>
#include <SDL_surface.h>
#include <SDL2\SDL_image.h>
#include <ft2build.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include FT_FREETYPE_H

namespace NovelRT {
    class NovelAssetLoader {
    public:
        NovelAssetLoader(char* path);

        std::string loadShader(std::string filename);
        FT_Face loadFont(std::string filename, FT_Library* fontLoader);
        SDL_Surface* loadImage(std::string filename);
        Mix_Chunk* loadAudio(std::string filename);

    protected:
        //Path to the executable, used to locate asset folders.
        std::string modulePath;
        //Shader Folder
        const std::string& shaderFolder = "\\Shaders\\";
        //Images Folder
        const std::string& imagesFolder = "\\Images\\";
        //Fonts Folder
        const std::string& fontsFolder = "\\Fonts\\";
        const std::string& audioFolder = "\\Audio\\";

    private:
        std::string getDirectory(std::string path);
        
    };
}

#endif
