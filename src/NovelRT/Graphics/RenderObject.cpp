// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics
{

    RenderObject::RenderObject(Transform transform,
                               int32_t layer,
                               ShaderProgram shaderProgram,
                               std::shared_ptr<Camera> camera)
        : WorldObject(transform, layer),
          _vertexBuffer(Utilities::Lazy<GLuint>(std::function<GLuint()>(generateStandardBuffer))),
          _vertexArrayObject(Utilities::Lazy<GLuint>(std::function<GLuint()>([] {
              GLuint tempVao;
              glGenVertexArrays(1, &tempVao);
              return tempVao;
          }))),
          _shaderProgram(shaderProgram),
          _bufferInitialised(false),
          _camera(camera),
          _finalViewMatrixData(Utilities::Lazy<Maths::GeoMatrix4x4F>(
              std::function<Maths::GeoMatrix4x4F()>(std::bind(&RenderObject::generateViewData, this))))
    {
    }

    void RenderObject::executeObjectBehaviour()
    {
        if (_camera->getFrameState() != CameraFrameState::Unmodified)
            _isDirty = true;

        if (_isDirty)
        {
            _finalViewMatrixData.reset();
            _bufferInitialised = false;
            _isDirty = false;
        }

        if (!_bufferInitialised)
        {
            configureObjectBuffers();
            _bufferInitialised = true;
        }
        drawObject();
    }

    void RenderObject::configureObjectBuffers()
    {
        auto topLeft = Maths::GeoVector2F(-0.5f, 0.5f);
        auto bottomRight = Maths::GeoVector2F(0.5f, -0.5f);
        auto topRight = Maths::GeoVector2F(0.5f, 0.5f);
        auto bottomLeft = Maths::GeoVector2F(-0.5f, -0.5f);
        _vertexBufferData = {
            topLeft.x, topLeft.y, 0.0f, bottomRight.x, bottomRight.y, 0.0f, topRight.x,    topRight.y,    0.0f,
            topLeft.x, topLeft.y, 0.0f, bottomLeft.x,  bottomLeft.y,  0.0f, bottomRight.x, bottomRight.y, 0.0f,
        };

        _vertexArrayObject.getActual(); // this is just here to force initialisation.

        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.getActual());

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexBufferData.size(), _vertexBufferData.data(),
                     GL_STATIC_DRAW);
    }

    RenderObject::~RenderObject()
    {
        if (!_vertexArrayObject.isCreated())
            return;

        auto vao = _vertexArrayObject.getActual();
        glDeleteVertexArrays(1, &vao);
    }

    GLuint RenderObject::generateStandardBuffer()
    {
        GLuint tempBuffer;
        glGenBuffers(1, &tempBuffer);
        return tempBuffer;
    }

    Maths::GeoMatrix4x4F RenderObject::generateViewData()
    {
        auto position = *reinterpret_cast<glm::vec2*>(&(transform().position));
        auto defaultIdentity = Maths::GeoMatrix4x4F::getDefaultIdentity();
        auto resultMatrix = *reinterpret_cast<glm::mat4*>(&defaultIdentity);
        resultMatrix = glm::translate(resultMatrix, glm::vec3(position, layer()));
        resultMatrix = glm::rotate(resultMatrix, glm::radians(transform().rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        resultMatrix = glm::scale(resultMatrix, glm::vec3(*reinterpret_cast<glm::vec2*>(&(transform().scale)), 1.0f));
        auto cameraUboMatrix = _camera->getCameraUboMatrix();
        return Maths::GeoMatrix4x4F(glm::transpose(*reinterpret_cast<glm::mat4*>(&cameraUboMatrix) * resultMatrix));
    }

    Maths::GeoMatrix4x4F RenderObject::generateCameraBlock()
    {
        return _camera->getCameraUboMatrix();
    }
} // namespace NovelRT::Graphics
