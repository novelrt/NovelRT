// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {

  RenderObject::RenderObject(const Transform& transform, int layer, ShaderProgram shaderProgram, std::weak_ptr<Camera> camera) :
    WorldObject(transform, layer),
    _vertexBuffer(Utilities::Lazy<GLuint>(std::function<GLuint()>(generateStandardBuffer))),
    _vertexArrayObject(Utilities::Lazy<GLuint>(std::function<GLuint()>([] {
    GLuint tempVao;
    glGenVertexArrays(1, &tempVao);
    return tempVao;
      }))),
    _shaderProgram(shaderProgram),
    _bufferInitialised(false),
    _camera(camera),
    _finalViewMatrixData(Utilities::Lazy<Maths::GeoMatrix4<float>>(std::function<Maths::GeoMatrix4<float>()>(std::bind(&RenderObject::generateViewData, this)))){}

  void RenderObject::executeObjectBehaviour() {
    if (_camera.lock()->getFrameState() != CameraFrameState::Unmodified) _isDirty = true;
    
    if (_isDirty) {
      _finalViewMatrixData.reset();
      _bufferInitialised = false;
      _isDirty = false;
    }

    if (!_bufferInitialised) {
      configureObjectBuffers();
      _bufferInitialised = true;
    }
    drawObject();
  }

  void RenderObject::configureObjectBuffers() {
    auto topLeft = Maths::GeoVector<GLfloat>(-0.5f, 0.5f);
    auto bottomRight = Maths::GeoVector<GLfloat>(0.5f, -0.5f);
    auto topRight = Maths::GeoVector<GLfloat>(0.5f, 0.5f);
    auto bottomLeft = Maths::GeoVector<GLfloat>(-0.5f, -0.5f);
    _vertexBufferData = {
        topLeft.getX(), topLeft.getY(), 0.0f,
        bottomRight.getX(), bottomRight.getY(), 0.0f,
        topRight.getX(), topRight.getY(), 0.0f,
        topLeft.getX(), topLeft.getY(), 0.0f,
        bottomLeft.getX(), bottomLeft.getY(), 0.0f,
        bottomRight.getX(), bottomRight.getY(), 0.0f,
    };

    _vertexArrayObject.getActual(); //this is just here to force initialisation.

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.getActual());

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexBufferData.size(), _vertexBufferData.data(), GL_STATIC_DRAW);
  }

  RenderObject::~RenderObject() {
    if (!_vertexArrayObject.isCreated()) return;

    auto vao = _vertexArrayObject.getActual();
    glDeleteVertexArrays(1, &vao);
  }

  GLuint RenderObject::generateStandardBuffer() {
    GLuint tempBuffer;
    glGenBuffers(1, &tempBuffer);
    return tempBuffer;
  }

  Maths::GeoMatrix4<float> RenderObject::generateViewData() {
    auto position = transform().position().getVec2Value();
    auto resultMatrix = Maths::GeoMatrix4<float>::getDefaultIdentity().getUnderlyingMatrix();
    resultMatrix = glm::translate(resultMatrix, glm::vec3(position, layer()));
    resultMatrix = glm::rotate(resultMatrix, glm::radians(transform().getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
    resultMatrix = glm::scale(resultMatrix, glm::vec3(transform().getScale().getVec2Value(), 1.0f));

    return Maths::GeoMatrix4<float>(glm::transpose(_camera.lock()->getCameraUboMatrix().getUnderlyingMatrix() * resultMatrix));
  }

  Maths::GeoMatrix4<float> RenderObject::generateCameraBlock() {
    return _camera.lock()->getCameraUboMatrix();
  }
}
