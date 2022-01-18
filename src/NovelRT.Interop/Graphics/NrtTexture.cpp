// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtTexture.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_Texture_loadPngAsTexture(NrtTextureHandle targetTexture, const char* file)
    {
        if (targetTexture == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);

        try
        {
            texturePtr->loadPngAsTexture(std::string(file));
        }
        catch (const Exceptions::InvalidOperationException)
        {
            return Nrt_getInvalidOperationErrorInternal();
        }

        return NRT_SUCCESS;
    }

    const char* Nrt_Texture_getTextureFile(NrtTextureHandle targetTexture)
    {
        Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
        return texturePtr->getTextureFile().c_str();
    }

    NrtGeoVector2F Nrt_Texture_getSize(NrtTextureHandle targetTexture)
    {
        Texture* texturePtr = reinterpret_cast<Texture*>(targetTexture);
        auto vec = texturePtr->getSize();
        return *reinterpret_cast<NrtGeoVector2F*>(&vec);
    }

#ifdef __cplusplus
}
#endif
