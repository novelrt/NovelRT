// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#define GL_GLEXT_PROTOTYPES

namespace NovelRT::Graphics {
  bool RenderingService::initialiseRenderPipeline() {

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    auto windowSize = _windowingService->getWindowSize();


    _camera->setProjectionMatrix(Maths::GeoMatrix4<float>(glm::ortho<float>(0, windowSize.getX(), windowSize.getY(), 0)));
    _camera->setViewMatrix(Maths::GeoMatrix4<float>(glm::scale(glm::vec3(windowSize.getX() / 1920.0f, windowSize.getY() / 1080.0f, -1.0f))));
    std::string infoScreenSize = std::to_string((int)windowSize.getX());
    infoScreenSize.append("x");
    infoScreenSize.append(std::to_string((int)windowSize.getY()));
    _logger.logInfo("Screen size:", infoScreenSize);

    _openGLContext = SDL_GL_CreateContext(_windowingService->getWindow());
    SDL_GL_MakeCurrent(_windowingService->getWindow(), _openGLContext);

    if (!gladLoadGL()) {
      _logger.logErrorLine("Failed to initialise glad.");
      throw std::runtime_error("Unable to continue! The engine cannot start without glad.");
    }

    std::string glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    std::string glShading = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    _logger.logInfoLine("GL_VERSION: " + glVersion);
    _logger.logInfoLine("GL_SHADING_LANGUAGE_VERSION: " + glShading);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _basicFillRectProgram = loadShaders("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
    _texturedRectProgram = loadShaders("TexturedVertexShader.glsl", "TexturedFragmentShader.glsl");
    _fontProgram = loadShaders("FontVertexShader.glsl", "FontFragmentShader.glsl");
    return true;
  }

  ShaderProgram RenderingService::loadShaders(std::string vertexFilePath, std::string fragmentFilePath) {

    // Create the shaders
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;

    std::ifstream VertexShaderStream(vertexFilePath, std::ios::in);
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
    std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
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
    _logger.logInfoLine("Compiling shader: " + vertexFilePath + "...");
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer, nullptr);
    glCompileShader(vertexShaderId);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
      std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
      glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
      _logger.logErrorLine(std::string(&vertexShaderErrorMessage[0]));
      throw std::runtime_error("Unable to continue! Please fix the compile time error in the specified shader.");
    }

    // Compile Fragment Shader
    _logger.logInfoLine("Compiling shader: " + fragmentFilePath + "...");
    const char* FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(fragmentShaderId);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
      std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
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
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
      std::vector<char> ProgramErrorMessage(infoLogLength + 1);
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
      _logger.logErrorLine("Apologies, something went wrong. Reason: SDL could not initialise.");
      throw std::runtime_error("Unable to continue! The engine cannot start without SDL2.");
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
  }

  void RenderingService::endFrame() const {
    SDL_GL_SwapWindow(_windowingService->getWindow());
  }

  std::unique_ptr<ImageRect> RenderingService::createImageRect(const Transform& transform,
    int layer,
    const std::string& filePath,
    const RGBAConfig& colourTint) {
    return std::make_unique<ImageRect>(transform, layer, _texturedRectProgram, getCamera(), filePath, colourTint);
  }

  std::unique_ptr<TextRect> RenderingService::createTextRect(const Transform& transform,
    int layer,
    const RGBAConfig& colourConfig,
    float fontSize,
    const std::string& fontFilePath) {
    return std::make_unique<TextRect>(transform, layer, _fontProgram, getCamera(), fontSize, fontFilePath, colourConfig);
  }

  RenderingService::RenderingService(Windowing::WindowingService* const windowingService) :
    _logger(LoggingService(Utilities::Misc::CONSOLE_LOG_GFX)),
    _windowingService(windowingService),
    _cameraObjectRenderUbo(std::function<GLuint()>([] {
    GLuint tempHandle;
    glGenBuffers(1, &tempHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, tempHandle);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Maths::GeoMatrix4<float>), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, tempHandle, 0, sizeof(Maths::GeoMatrix4<float>));
    return tempHandle;
      })),
    _camera(std::make_unique<Camera>()) {}

  std::unique_ptr<BasicFillRect> RenderingService::createBasicFillRect(const Transform& transform, int layer, const RGBAConfig& colourConfig) {
    return std::make_unique<BasicFillRect>(transform, layer, getCamera(), _basicFillRectProgram, colourConfig);
  }

  Camera* RenderingService::getCamera() const {
    return _camera.get();
  }

  void RenderingService::bindCameraUboForProgram(GLuint shaderProgramId) {
    GLuint uboIndex = glGetUniformBlockIndex(shaderProgramId, "finalViewMatrixBuffer");
    glUniformBlockBinding(shaderProgramId, uboIndex, 0);
  }
}
