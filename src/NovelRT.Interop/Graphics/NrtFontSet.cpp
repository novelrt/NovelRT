
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtFontSet.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtResult Nrt_FontSet_loadFontAsTextureSet(NrtFontSetHandle fontSet, const char* file, float fontSize)
    {
        if (fontSet == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);

        try
        {
            fontSetPtr->loadFontAsTextureSet(std::string(file), fontSize);
        }
        catch (const Exceptions::InvalidOperationException)
        {
            return Nrt_getInvalidOperationErrorInternal();
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_FontSet_getFontFile(NrtFontSetHandle fontSet, const char** outputFontFile)
    {
        if (fontSet == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);
        *outputFontFile = fontSetPtr->getFontFile().c_str();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_FontSet_getFontSize(NrtFontSetHandle fontSet, float* outputFontSize)
    {
        if (fontSet == nullptr)
        {
            return Nrt_getNullInstanceErrorInternal();
        }

        if (outputFontSize == nullptr)
        {
            return Nrt_getNullArgumentErrorInternal();
        }

        FontSet* fontSetPtr = reinterpret_cast<FontSet*>(fontSet);
        *outputFontSize = fontSetPtr->getFontSize();

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
