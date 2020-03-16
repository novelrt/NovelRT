// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  Texture::Texture(std::weak_ptr<RenderingService> renderer, Atom id) :
    _id(id),
    _renderer(renderer),
    _textureId(Utilities::Lazy<GLuint>([] {
    GLuint tempTexture;
    glGenTextures(1, &tempTexture);
    return tempTexture;
    })),
    _logger(Utilities::Misc::CONSOLE_LOG_GFX){}

  void Texture::loadPngAsTexture(const std::string& file) {
    if (_textureId.isCreated()) {
      _logger.logErrorLine("This texture has already been initialised with data. Please make a new texture!");
      throw std::runtime_error("Unable to continue! Cannot overwrite Texture!");
    }
    _textureFile = file;
    //The following libpng setup SHOULD always force it to RGBA, and should always ensure the bit size is the same

    FILE* cFile;
#if defined(__STDC_LIB_EXT1__) || defined(_MSC_VER)
    _logger.throwIfNotZero(fopen_s(&cFile, file.c_str(), "rb"), "Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");
#else
    cFile = fopen(file.c_str(), "rb");
#endif
    auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr); //TODO: Figure out how the error function ptr works

    if (png == nullptr) {
      _logger.logErrorLine("Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");
      throw std::runtime_error("Unable to continue! File failed to load for texture.");
    }

    auto info = png_create_info_struct(png);

    if (info == nullptr) {
      _logger.logError("Image at path " + file + " failed to provide an info struct! Aborting...");
      throw std::runtime_error("Unable to continue! File failed to load for texture.");
    }

    if (setjmp(png_jmpbuf(png))) { //This is how libpng does error handling.
      _logger.logError("Image at path " + file + " appears to be corrupted! Aborting...");
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
    auto bpp = static_cast<uint32_t>(rowBytes) / data.width;

    //Allows us to get the final image data, not interlaced.
    png_set_interlace_handling(png);

    //Props to Kenny for debugging this without asking me and saving me the mental strain lmao
    auto pixelBufferAmount = (data.width * data.height * bpp);
    auto rawImage = new unsigned char[pixelBufferAmount]; //We allocate the pixel buffer here.
    if (rawImage == nullptr) {
      png_destroy_read_struct(&png, &info, nullptr);
      fclose(cFile);
      throw std::runtime_error("Couldn't allocate space for PNG!");
    }

    data.rowPointers = new png_bytep[data.height];  //Setup row pointer array and set it into the pixel buffer.
    unsigned char* p = rawImage;

    //TODO: Proper error check on data.rowPointers
    if (data.rowPointers == nullptr) {
      _logger.logErrorLine("Unable to continue! Couldn't allocate memory for the PNG pixel data! Aborting...");
      throw std::runtime_error("Unable to continue! File failed to load for texture.");
    }

    for (uint32_t i = 0; i < data.height; i++) {
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

    _size = Maths::GeoVector2<float>(static_cast<float>(data.width), static_cast<float>(data.height));

    fclose(cFile);
    delete[] rawImage;
    delete[] data.rowPointers;
    png_destroy_read_struct(&png, &info, nullptr);
  }

  Texture::~Texture() {
    if(!_renderer.expired()) _renderer.lock()->handleTexturePreDestruction(this);


    if (!_textureId.isCreated()) return;

    auto textureId = _textureId.getActual();
    glDeleteTextures(1, &textureId);
  }
}
