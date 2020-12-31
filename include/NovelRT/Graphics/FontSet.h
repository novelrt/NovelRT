// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#ifndef NOVELRT_GRAPHICS_FONTSET_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

#include "NovelRT/Exceptions/CharacterNotFoundException.h"

namespace NovelRT::Graphics
{
    class FontSet : public std::enable_shared_from_this<FontSet>
    {
        friend class ImageRect;
        friend class TextRect;
        friend class RenderingService;

      private:
        std::shared_ptr<RenderingService> _renderer;
        Atom _id;
        float _fontSize;
        std::vector<GraphicsCharacterRenderData> _characters;
        LoggingService _logger; // not proud of this
        std::string _fontFile;
        std::map<GLchar, GraphicsCharacterRenderData> _fontCharacters;

        inline const std::vector<GraphicsCharacterRenderData>& getCharacterRenderDataInternal() const noexcept
        {
            return _characters;
        }

        inline Atom getId() const noexcept
        {
            return _id;
        }

        inline GraphicsCharacterRenderData getCharacterBasedonGLchar(char c) const
        {
            auto match = _fontCharacters.find(c);
            if (match == _fontCharacters.end())
            {
                match = _fontCharacters.begin();
            }

            if (match == _fontCharacters.end())
            {
                throw Exceptions::CharacterNotFoundException(c);
            }

            return match->second;
        }

      public:
        FontSet(std::shared_ptr<RenderingService> renderer, Atom id) noexcept;

        void loadFontAsTextureSet(const std::string& file, float fontSize);

        inline std::string getFontFile() const noexcept
        {
            return _fontFile;
        }

        inline float getFontSize() const noexcept
        {
            return _fontSize;
        }

        ~FontSet();
    };
} // namespace NovelRT::Graphics

#endif //! NOVELRT_GRAPHICS_FONTSET_H
