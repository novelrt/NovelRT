// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_RENDEROBJECT_H
#define NOVELRT_GRAPHICS_RENDEROBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT::Graphics
{
    class RenderObject : public WorldObject
    {
    protected:
        virtual void drawObject() = 0;
        virtual void configureObjectBuffers();
        static GLuint generateStandardBuffer() noexcept;
        Maths::GeoMatrix4x4F generateViewData() noexcept;
        Maths::GeoMatrix4x4F generateCameraBlock();

        Utilities::Lazy<GLuint> _vertexBuffer;
        Utilities::Lazy<GLuint> _vertexArrayObject;
        ShaderProgram _shaderProgram;
        std::vector<GLfloat> _vertexBufferData;
        bool _bufferInitialised;
        std::shared_ptr<Camera> _camera;
        Utilities::Lazy<Maths::GeoMatrix4x4F> _finalViewMatrixData;

    public:
        RenderObject(Transform transform, int32_t layer, ShaderProgram shaderProgram, std::shared_ptr<Camera> camera);

        void executeObjectBehaviour() final;
        virtual ~RenderObject();
    };
}

#endif // NOVELRT_GRAPHICS_RENDEROBJECT_H
