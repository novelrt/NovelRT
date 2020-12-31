// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_BASICFILLRECT_H
#define NOVELRT_GRAPHICS_BASICFILLRECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics
{
    class BasicFillRect : public RenderObject
    {

      private:
        RGBAConfig _colourConfig;
        Utilities::Lazy<GLuint> _colourBuffer;
        std::vector<GLfloat> _colourData;

      protected:
        void configureObjectBuffers() final;
        void drawObject() final;

      public:
        BasicFillRect(Transform transform, int32_t layer, std::shared_ptr<Camera> camera, ShaderProgram shaderProgram,
                      RGBAConfig fillColour);

        RGBAConfig getColourConfig() const;
        void setColourConfig(RGBAConfig value);
    };
} // namespace NovelRT::Graphics

#endif // NOVELRT_GRAPHICS_BASICFILLRECT_H
