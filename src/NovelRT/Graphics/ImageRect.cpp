// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  ImageRect::ImageRect(const Transform& transform,
    int layer,
    ShaderProgram shaderProgram,
    Camera* camera,
    const std::string& imageDir,
    const RGBAConfig& colourTint) :
    RenderObject(transform,
      layer,
      shaderProgram,
      camera),
    _imageDir(imageDir),
    _textureId(Utilities::Lazy<GLuint>([] {
    GLuint tempTexture;
    glGenTextures(1, &tempTexture);
    return tempTexture;
      })),
    _uvBuffer(Utilities::Lazy<GLuint>(generateStandardBuffer)),
        _colourTintBuffer(Utilities::Lazy<GLuint>(generateStandardBuffer)),
        _colourTint(colourTint),
        _logger(Utilities::Misc::CONSOLE_LOG_GFX) {}

      ImageRect::ImageRect(const Transform& transform,
        int layer,
        ShaderProgram shaderProgram,
        Camera* camera,
        const RGBAConfig& colourTint) : ImageRect(transform, layer, shaderProgram, camera, "", colourTint) {
      }

      void ImageRect::drawObject() {
        if (!getActive())
          return;

        glUseProgram(_shaderProgram.shaderProgramId);
        glBindBuffer(GL_UNIFORM_BUFFER, _shaderProgram.finalViewMatrixBufferUboId);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(Maths::GeoMatrix4<float>), &_finalViewMatrixData.getActual(), GL_STATIC_DRAW);

        glBindTexture(GL_TEXTURE_2D, _textureId.getActual());
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

        if (_imageDir.empty() || _imageDir == _previousImageDir) return;

        _previousImageDir = _imageDir;

        //The following libpng setup SHOULD always force it to RGBA, and should always ensure the bit size is the same

        auto cFile = fopen(_imageDir.c_str(), "rb");
        auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr); //TODO: Figure out how the error function ptr works

        _logger.throwIfNullPtr(png, "Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");

        auto info = png_create_info_struct(png);

        _logger.throwIfNullPtr(info, "Image at path " + _imageDir + " failed to provide an info struct! Aborting...");

        if (setjmp(png_jmpbuf(png))) { //This is how libpng does error handling.
          _logger.logError("Image at path " + _imageDir + " appears to be corrupted! Aborting...");
          throw std::runtime_error("Unable to continue! File failed to load for texture.");
        }

        png_init_io(png, cFile);
        png_read_info(png, info);

        ImageData data;
        data.width = png_get_image_width(png, info);
        data.height = png_get_image_height(png, info);
        data.colourType = png_get_color_type(png, info);
        data.bitDepth = png_get_bit_depth(png, info);

        if (data.bitDepth == 16) png_set_strip_16(png);

        if (data.colourType == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);

        if (data.colourType == PNG_COLOR_TYPE_GRAY && data.bitDepth < 8) png_set_expand_gray_1_2_4_to_8(png);

        if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);

        if (data.colourType == PNG_COLOR_TYPE_RGB ||
          data.colourType == PNG_COLOR_TYPE_GRAY ||
          data.colourType == PNG_COLOR_TYPE_PALETTE) { //id one line this but it looks ugly
          png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
        }

        if (data.colourType == PNG_COLOR_TYPE_GRAY || data.colourType == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png);

        png_read_update_info(png, info);

        
        auto rowBytes = png_get_rowbytes(png, info);
        auto bpp = (unsigned int)(rowBytes) / data.width;

        //Allows us to get the final image data, not interlaced.
        png_set_interlace_handling(png);

        //Props to Kenny for debugging this without asking me and saving me the mental strain lmao
        auto pixelBufferAmount = (data.width * data.height * bpp);
        auto rawImage = new unsigned char[pixelBufferAmount]; //We allocate the pixel buffer here.
        if (rawImage == nullptr) {
          png_destroy_read_struct(&png, &info, (png_infopp)nullptr);
          fclose(cFile);
          throw std::runtime_error("Couldn't allocate space for PNG!");
        }

        data.rowPointers = new png_bytep[data.height];  //Setup row pointer array and set it into the pixel buffer.
        unsigned char* p = rawImage;

        //TODO: Proper error check on data.rowPointers
        _logger.throwIfNullPtr(data.rowPointers, "Unable to continue! Couldn't allocate memory for the PNG pixel data! Aborting...");

        for (int i = 0; i < data.height; i++) {
          data.rowPointers[i] = p;
          p += data.width * bpp;
        }

        //Read all the rows (data will flow into the pixel buffer)
        png_read_image(png, data.rowPointers);
        png_read_end(png, info);  //Finish reading the file - this will also check for corruption

        glBindTexture(GL_TEXTURE_2D, _textureId.getActual());

        int mode = GL_RGBA;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, mode, data.width, data.height, 0, mode, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(rawImage));
        glGenerateMipmap(GL_TEXTURE_2D);

        fclose(cFile);
        delete[] rawImage;
        delete[] data.rowPointers;
        png_destroy_read_struct(&png, &info, nullptr);
      }

      void ImageRect::setTextureInternal(GLuint textureId) {
        _imageDir = "";
        _textureId = Utilities::Lazy<GLuint>(textureId, [] {
          GLuint tempBuffer;
          glGenBuffers(1, &tempBuffer);
          return tempBuffer;
          });
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

      ImageRect::~ImageRect() {
        if (_imageDir.empty() && !_textureId.isCreated()) return;

        auto textureId = _textureId.getActual();
        glDeleteTextures(1, &textureId);
      }

}
