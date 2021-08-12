// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Graphics/NrtTextRect.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.h>

using namespace NovelRT::Graphics;
using namespace NovelRT::Maths;
using namespace NovelRT;

#ifdef __cplusplus
extern "C"
{
#endif

    NrtTransform Nrt_TextRect_getTransform(NrtTextRectHandle rect)
    {
        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        Transform cppTransform = textRectPtr->transform();
        return *reinterpret_cast<NrtTransform*>(&cppTransform);
    }

    NrtResult Nrt_TextRect_setTransform(NrtTextRectHandle rect, NrtTransform inputTransform)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        textRectPtr->transform() = *reinterpret_cast<Transform*>(&inputTransform);

        return NRT_SUCCESS;
    }

    int32_t Nrt_TextRect_getLayer(NrtTextRectHandle rect)
    {
        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        return textRectPtr->layer();
    }

    NrtResult Nrt_TextRect_setLayer(NrtTextRectHandle rect, int32_t inputLayer)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        textRectPtr->layer() = inputLayer;

        return NRT_SUCCESS;
    }

    NrtBool Nrt_TextRect_getActive(NrtTextRectHandle rect)
    {
        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

        if (textRectPtr->getActive())
        {
            return NRT_TRUE;
        }
        return NRT_FALSE;
    }

    NrtResult Nrt_TextRect_setActive(NrtTextRectHandle rect, NrtBool inputBool)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

        if (inputBool == NRT_TRUE)
        {
            textRectPtr->setActive(true);
        }
        else
        {
            textRectPtr->setActive(false);
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_executeObjectBehaviour(NrtTextRectHandle rect)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);

        textRectPtr->executeObjectBehaviour();

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_getColourConfig(NrtTextRectHandle rect, NrtRGBAConfigHandle* outputColourConfig)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputColourConfig == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        auto colourConfig = new RGBAConfig(0, 0, 0, 0);
        *colourConfig = textRectPtr->getColourConfig();
        *outputColourConfig = reinterpret_cast<NrtRGBAConfigHandle>(colourConfig);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_setColourConfig(NrtTextRectHandle rect, NrtRGBAConfigHandle inputColourConfig)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        textRectPtr->setColourConfig(*reinterpret_cast<RGBAConfig*>(inputColourConfig));

        return NRT_SUCCESS;
    }

    const char* Nrt_TextRect_getText(NrtTextRectHandle rect)
    {
        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        std::string* text = new std::string(textRectPtr->getText());
        return text->c_str();
    }

    NrtResult Nrt_TextRect_setText(NrtTextRectHandle rect, const char* inputText)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        try
        {
            textRectPtr->setText(std::string(inputText));
        }
        catch (const Exceptions::CharacterNotFoundException)
        {
            Nrt_setErrMsgIsCharacterNotFoundInternal();
            return NRT_FAILURE_CHARACTER_NOT_FOUND;
        }

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_getFontSet(NrtTextRectHandle rect, NrtFontSetHandle* outputFontSet)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        if (outputFontSet == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        auto fontSet = textRectPtr->getFontSet();
        *outputFontSet = reinterpret_cast<NrtFontSetHandle>(fontSet.get());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_setFontSet(NrtTextRectHandle rect, NrtFontSetHandle inputFontSet)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        TextRect* textRectPtr = reinterpret_cast<TextRect*>(rect);
        textRectPtr->setFontSet(reinterpret_cast<FontSet*>(inputFontSet)->shared_from_this());

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_getAsRenderObjectPtr(NrtTextRectHandle rect, NrtRenderObjectHandle* outputRenderObject)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_ARGUMENT_PROVIDED;
        }

        *outputRenderObject = reinterpret_cast<NrtRenderObjectHandle>(rect);

        return NRT_SUCCESS;
    }

    NrtResult Nrt_TextRect_destroy(NrtTextRectHandle rect)
    {
        if (rect == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULL_INSTANCE_PROVIDED;
        }

        delete reinterpret_cast<TextRect*>(rect);

        return NRT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif
