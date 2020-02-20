// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  ImageRect::ImageRect(const Transform& transform,
    int layer,
    ShaderProgram shaderProgram,
    Camera* camera,
    std::shared_ptr<Texture> texture,
    const RGBAConfig& colourTint) :
    RenderObject(transform,
      layer,
      shaderProgram,
      camera),
    _texture(texture),
    _uvBuffer(Utilities::Lazy<GLuint>(generateStandardBuffer)),
    _colourTintBuffer(Utilities::Lazy<GLuint>(generateStandardBuffer)),
    _colourTint(colourTint),
    _logger(Utilities::Misc::CONSOLE_LOG_GFX) {}

   ImageRect::ImageRect(const Transform& transform,
     int layer,
     ShaderProgram shaderProgram,
     Camera* camera,
     const RGBAConfig& colourTint) : ImageRect(transform, layer, shaderProgram, camera, nullptr, colourTint) {
   }

   void ImageRect::drawObject() {
     if (!getActive() || _texture == nullptr) return;

     glUseProgram(_shaderProgram.shaderProgramId);
     glBindBuffer(GL_UNIFORM_BUFFER, _shaderProgram.finalViewMatrixBufferUboId);
     glBufferData(GL_UNIFORM_BUFFER, sizeof(Maths::GeoMatrix4<float>), &_finalViewMatrixData.getActual(), GL_STATIC_DRAW);

     glBindTexture(GL_TEXTURE_2D, _texture->getTextureIdInternal());
     glBindVertexArray(_vertexArrayObject.getActual());
     glEnableVertexAttribArray(0);
     glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.getActual());
     glVertexAttribPointer(
       0,
       3,
       GL_FLOAT,
       GL_FALSE,
       0,
       nullptr
     );

     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer.getActual());
     glVertexAttribPointer(
       1,
       2,
       GL_FLOAT,
       GL_FALSE,
       0,
       nullptr
     );

     glEnableVertexAttribArray(2);
     glBindBuffer(GL_ARRAY_BUFFER, _colourTintBuffer.getActual());
     glVertexAttribPointer(
       2,
       4,
       GL_FLOAT,
       GL_FALSE,
       0,
       nullptr
     );

     glDrawArrays(GL_TRIANGLES, 0, 6);
     glDisableVertexAttribArray(2);
     glDisableVertexAttribArray(1);
     glDisableVertexAttribArray(0);
     glBindVertexArray(0);
   }

   void ImageRect::configureObjectBuffers() {
     RenderObject::configureObjectBuffers();

     _uvCoordinates = {
         0.0f, 1.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
         1.0f, 0.0f
     };

     glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer.getActual());

     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _uvCoordinates.size(), _uvCoordinates.data(), GL_STATIC_DRAW);

     auto config = getColourTintConfig();
     auto rScalar = config.getRScalar();
     auto gScalar = config.getGScalar();
     auto bScalar = config.getBScalar();
     auto aScalar = config.getAScalar();

     _colourTintData = {
         rScalar, gScalar, bScalar, aScalar,
         rScalar, gScalar, bScalar, aScalar,
         rScalar, gScalar, bScalar, aScalar,
         rScalar, gScalar, bScalar, aScalar,
         rScalar, gScalar, bScalar, aScalar,
         rScalar, gScalar, bScalar, aScalar,
     };

     glBindBuffer(GL_ARRAY_BUFFER, _colourTintBuffer.getActual());
     glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _colourTintData.size(), _colourTintData.data(), GL_STATIC_DRAW);
   }

   void ImageRect::setTexture(std::shared_ptr<Texture> texture) {
     _texture = texture;
   }
   const RGBAConfig& ImageRect::getColourTintConfig() const {
     return _colourTint;
   }
   RGBAConfig& ImageRect::getColourTintConfig() {
     return _colourTint;
   }
   void ImageRect::setColourTintConfig(const RGBAConfig& value) {
     _colourTint = value;
   }
}
