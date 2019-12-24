// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <iostream>
#include <NovelRT.h>
#include <functional>

namespace NovelRT::Graphics {

  void RenderObject::OnCameraViewChanged(CameraViewChangedEventArgs args) {
    _uboCameraData = CameraBlock(args.cameraMatrix.getUnderlyingMatrix());
  }

  RenderObject::RenderObject(const Transform& transform, ShaderProgram shaderProgram, Camera* camera) :
    WorldObject(transform),
    _finalViewMatrixData(Utilities::Lazy<CameraBlock>(std::function<CameraBlock()>(std::bind(&RenderObject::generateViewData, this)))),
    _vertexBuffer(Utilities::Lazy<GLuint>(std::function<GLuint()>(generateStandardBuffer))),
    _vertexArrayObject(Utilities::Lazy<GLuint>(std::function<GLuint()>([] {
    GLuint tempVao;
    glGenVertexArrays(1, &tempVao);
    return tempVao;
      }))),
    _shaderProgram(shaderProgram),
    _camera(camera),
    _uboCameraData(CameraBlock(_camera->getCameraUboMatrix().getUnderlyingMatrix())) {
    _camera->subscribeToCameraViewChanged([this](auto x) { OnCameraViewChanged(x); }); //TODO: Should we refactor the method into the lambda?
  }

  void RenderObject::executeObjectBehaviour() {
    if (!_bufferInitialised || _isDirty) {
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

  CameraBlock RenderObject::generateViewData() {
    auto position = getTransform().getPosition().getVec2Value();
    auto resultMatrix = Maths::GeoMatrix4<float>::getDefaultIdentity().getUnderlyingMatrix();
    resultMatrix = glm::translate(resultMatrix, glm::vec3(position, 0.0f));
    resultMatrix = glm::rotate(resultMatrix, glm::radians(getTransform().getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
    resultMatrix = glm::scale(resultMatrix, glm::vec3(getTransform().getScale().getVec2Value(), 1.0f));

    return CameraBlock(glm::transpose(_uboCameraData.cameraMatrix * resultMatrix));
  }

  CameraBlock RenderObject::generateCameraBlock() {
    return CameraBlock(_camera->getCameraUboMatrix().getUnderlyingMatrix());
  }
}
