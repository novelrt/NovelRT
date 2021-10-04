// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_TEXTRECT_H
#define NOVELRT_GRAPHICS_TEXTRECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics
{
    class TextRect : public RenderObject
    {

    private:
        void reloadText();

        std::string _fontFileDir;
        std::string _previousFontFileDir;
        std::string _text;
        std::vector<std::unique_ptr<ImageRect>> _letterRects;
        LoggingService _logger;
        RGBAColour _colourConfig;
        std::shared_ptr<FontSet> _fontSet;

    protected:
        void configureObjectBuffers() final;
        void drawObject() final;

    public:
        TextRect(Transform transform,
                 int32_t layer,
                 ShaderProgram programId,
                 std::shared_ptr<Camera> camera,
                 std::shared_ptr<FontSet> fontSet,
                 RGBAColour colourConfig);

        inline RGBAColour getColourConfig() const noexcept
        {
            return _colourConfig;
        }

        void setColourConfig(RGBAColour value);

        std::string getText() const noexcept;
        void setText(const std::string& value);

        void setActive(bool value) noexcept override;

        inline std::shared_ptr<FontSet> getFontSet() const noexcept
        {
            return _fontSet;
        }

        inline void setFontSet(std::shared_ptr<FontSet> value) noexcept
        {
            _fontSet = value;
        }
    };
}

#endif // NOVELRT_GRAPHICS_TEXTRECT_H
