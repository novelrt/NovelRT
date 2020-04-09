// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>

namespace NovelRT::Graphics {
  RenderingService::RenderingService(NovelRunner* const runner) :
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_GFX)),
    _runner(runner),
    _cameraObjectRenderUbo(std::function<GLuint()>([] {
      GLuint tempHandle;
      glGenBuffers(1, &tempHandle);
      glBindBuffer(GL_UNIFORM_BUFFER, tempHandle);
      glBufferData(GL_UNIFORM_BUFFER, sizeof(Maths::GeoMatrix4x4<float>), nullptr, GL_STATIC_DRAW);
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
      glBindBufferRange(GL_UNIFORM_BUFFER, 0, tempHandle, 0, sizeof(Maths::GeoMatrix4x4<float>));
      return tempHandle;
    })),
    _camera(nullptr) {
      auto ptr = _runner->getWindowingService();
      if(!ptr.expired()) ptr.lock()->WindowResized += ([this](auto input) {
        initialiseRenderPipeline(false, &input);
      });
  }

  bool RenderingService::initialiseRenderPipeline(bool completeLaunch, Maths::GeoVector2<float>* const optionalWindowSize) {

    auto windowSize = (optionalWindowSize == nullptr) ? _runner->getWindowingService().lock()->getWindowSize() : *optionalWindowSize; //lol this is not safe

    std::string infoScreenSize = std::to_string(static_cast<int>(windowSize.getX()));
    infoScreenSize.append("x");
    infoScreenSize.append(std::to_string(static_cast<int>(windowSize.getY())));
    _logger.logInfo("Screen size:", infoScreenSize);

    if (completeLaunch) {
      _camera = Camera::createDefaultOrthographicProjection(windowSize);
      glfwMakeContextCurrent(_runner->getWindowingService().lock()->getWindow()); //lmao

      if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        _logger.logErrorLine("Failed to initialise glad.");
        throw std::runtime_error("Unable to continue! The engine cannot start without glad.");
      }

      std::string glVendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
      _logger.logInfoLine("GL_VENDOR: " + glVendor);

      std::string glRenderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
      _logger.logInfoLine("GL_RENDERER: " + glRenderer);

      std::string glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
      _logger.logInfoLine("GL_VERSION: " + glVersion);

      std::string glShading = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
      _logger.logInfoLine("GL_SHADING_LANGUAGE_VERSION: " + glShading);

      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      _basicFillRectProgram = loadShaders("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
      _texturedRectProgram = loadShaders("TexturedVertexShader.glsl", "TexturedFragmentShader.glsl");
      _fontProgram = loadShaders("FontVertexShader.glsl", "FontFragmentShader.glsl");
    }
    else {
      _camera->forceResize(windowSize);
      glViewport(0, 0, static_cast<GLsizei>(windowSize.getX()), static_cast<GLsizei>(windowSize.getY()));
    }

    return true;
  }

  ShaderProgram RenderingService::loadShaders(const std::string& vertexFileName, const std::string& fragmentFileName) {

    // Create the shaders
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    std::filesystem::path executableDirPath = Utilities::Misc::getExecutableDirPath();
    std::filesystem::path shadersDirPath = executableDirPath / "Resources" / "Shaders";

    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;

    std::ifstream VertexShaderStream(shadersDirPath / vertexFileName, std::ios::in);
    if (VertexShaderStream.is_open()) {
      std::stringstream sstr;
      sstr << VertexShaderStream.rdbuf();
      vertexShaderCode = sstr.str();
      VertexShaderStream.close();
    }
    else {
      _logger.logErrorLine("Target Vertex Shader file cannot be opened! Please ensure the path is correct and that the file is not locked.");
      throw EXIT_FAILURE;
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(shadersDirPath / fragmentFileName, std::ios::in);
    if (fragmentShaderStream.is_open()) {
      std::stringstream stringStream;
      stringStream << fragmentShaderStream.rdbuf();
      fragmentShaderCode = stringStream.str();
      fragmentShaderStream.close();
    }
    else {
      _logger.logErrorLine("Target Fragment Shader file cannot be opened! Please ensure the path is correct and that the file is not locked.");
      throw EXIT_FAILURE;
    }

    GLint Result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    _logger.logInfoLine("Compiling shader: " + vertexFileName + "...");
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer, nullptr);
    glCompileShader(vertexShaderId);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
      std::vector<char> vertexShaderErrorMessage(static_cast<size_t>(infoLogLength) + 1);
      glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
      _logger.logErrorLine(std::string(&vertexShaderErrorMessage[0]));
      throw std::runtime_error("Unable to continue! Please fix the compile time error in the specified shader.");
    }

    // Compile Fragment Shader
    _logger.logInfoLine("Compiling shader: " + fragmentFileName + "...");
    const char* FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(fragmentShaderId);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
    if (Result != GL_TRUE) {
      glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
      std::vector<char> fragmentShaderErrorMessage(static_cast<size_t>(infoLogLength) + 1);
      glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
      _logger.logErrorLine(std::string(&fragmentShaderErrorMessage[0]));
      throw std::runtime_error("Unable to continue! Please fix the compile time error in the specified shader.");
    }

    // Link the program
    _logger.logInfoLine("Linking program...");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &Result);
    if (Result != GL_TRUE) {
      glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
      std::vector<char> ProgramErrorMessage(static_cast<size_t>(infoLogLength) + 1);
      glGetProgramInfoLog(programId, infoLogLength, nullptr, &ProgramErrorMessage[0]);
      _logger.logErrorLine(std::string(&ProgramErrorMessage[0]));
      throw std::runtime_error("Unable to continue! Please fix the specified error in the shader program.");
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    ShaderProgram returnProg;
    returnProg.shaderProgramId = programId;
    returnProg.finalViewMatrixBufferUboId = _cameraObjectRenderUbo.getActual();
    bindCameraUboForProgram(programId);

    return returnProg;
  }

  int RenderingService::initialiseRendering() {
    if (!initialiseRenderPipeline()) {
      _logger.logErrorLine("Apologies, something went wrong.");
      throw std::runtime_error("Unable to continue! The engine cannot start without GLAD/GLFW3.");
    }

    return 0;
  }

  void RenderingService::tearDown() const {
    glDeleteProgram(_basicFillRectProgram.shaderProgramId);
    glDeleteProgram(_texturedRectProgram.shaderProgramId);
  }

  void RenderingService::beginFrame() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    _camera->initialiseCameraForFrame();
  }

  void RenderingService::endFrame() const {
    glfwSwapBuffers(_runner->getWindowingService().lock()->getWindow());
  }

  std::unique_ptr<ImageRect> RenderingService::createImageRect(const Transform& transform,
    int layer,
    const std::string& filePath,
    const RGBAConfig& colourTint) {
    return std::make_unique<ImageRect>(transform, layer, _texturedRectProgram, getCamera(), getTexture(filePath), colourTint);
  }

  std::unique_ptr<ImageRect> RenderingService::createImageRect(const Transform& transform,
    int layer,
    const RGBAConfig& colourTint) {
    return std::make_unique<ImageRect>(transform, layer, _texturedRectProgram, getCamera(), colourTint);
  }

  std::unique_ptr<TextRect> RenderingService::createTextRect(const Transform& transform,
    int layer,
    const RGBAConfig& colourConfig,
    float fontSize,
    const std::string& fontFilePath) {
    return std::make_unique<TextRect>(transform, layer, _fontProgram, getCamera(), getFontSet(fontFilePath, fontSize), colourConfig);
  }

  std::unique_ptr<BasicFillRect> RenderingService::createBasicFillRect(const Transform& transform, int layer, const RGBAConfig& colourConfig) noexcept {
    return std::make_unique<BasicFillRect>(transform, layer, getCamera(), _basicFillRectProgram, colourConfig);
  }

  std::weak_ptr<Camera> RenderingService::getCamera() const {
    return _camera;
  }

  void RenderingService::bindCameraUboForProgram(GLuint shaderProgramId) noexcept {
    GLuint uboIndex = glGetUniformBlockIndex(shaderProgramId, "finalViewMatrixBuffer");
    glUniformBlockBinding(shaderProgramId, uboIndex, 0);
  }

  void RenderingService::handleTexturePreDestruction(Texture* target) noexcept {
    _textureCache.erase(target->getId());
  }

  void RenderingService::handleFontSetPreDestruction(FontSet* target) noexcept {
    _fontCache.erase(target->getId());
  }

  std::shared_ptr<Texture> RenderingService::getTexture(const std::string& fileTarget) {
    if (!fileTarget.empty()) {
      for(auto& pair : _textureCache) {
        auto result = pair.second.lock();
        if (result->getTextureFile() != fileTarget) continue;

        return result;
      }

      auto returnValue = std::make_shared<Texture>(_runner->getRenderer(), Atom::getNextTextureId());
      std::weak_ptr<Texture> valueForMap = returnValue;
      _textureCache.emplace(returnValue->getId(), valueForMap);
      returnValue->loadPngAsTexture(fileTarget);
      return returnValue; 
    }

    //DRY, I know, but Im really not fussed rn
    auto returnValue = std::make_shared<Texture>(_runner->getRenderer(), Atom::getNextTextureId());
    std::weak_ptr<Texture> valueForMap = returnValue;
    _textureCache.emplace(returnValue->getId(), valueForMap);

    return returnValue;
  }

  std::shared_ptr<FontSet> RenderingService::getFontSet(const std::string& fileTarget, float fontSize) {
    if (!fileTarget.empty()) {
      for (auto& pair : _fontCache) {
        auto result = pair.second.lock();
        if (result->getFontFile() != fileTarget || result->getFontSize() != fontSize) continue;

        return result;
      }
    }

    auto returnValue = std::make_shared<FontSet>(_runner->getRenderer(), Atom::getNextFontSetId());
    _fontCache.emplace(returnValue->getId(), std::weak_ptr<FontSet>(returnValue));
    returnValue->loadFontAsTextureSet(fileTarget, fontSize);
    return returnValue;
  }
}
