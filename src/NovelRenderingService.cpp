#include "NovelRenderingService.h"
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRenderingService.h"

#include <SDL2/SDL.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include "GeoVector.h"
#include "NovelBasicFillRect.h"
#include "NovelImageRect.h"
#include "NovelUtilities.h"
#include <algorithm>
#include <fstream>
#include <sstream>

namespace NovelRT {
  bool NovelRenderingService::initialiseRenderPipeline(int displayNumber, const std::string& windowTitle) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
      _logger.logError("Could not initialize sdl2: ", std::string(SDL_GetError()));
      return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    SDL_DisplayMode displayData;
    SDL_GetCurrentDisplayMode(displayNumber, &displayData);


    // create window
    float wData = displayData.w * 0.7f;
    float hData = displayData.h * 0.7f;
    _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
      windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
    if (_window == nullptr) {
      _logger.logError("Could not create window: ", std::string(SDL_GetError()));

      return false;
    }
    _camera->setProjectionMatrix(GeoMatrix4<float>(glm::ortho<float>(0, wData, hData, 0)));
    _camera->setViewMatrix(GeoMatrix4<float>(glm::scale(glm::vec3(wData / 1920.0f, hData / 1080.0f, 0.0f))));
    _screenSize = GeoVector<float>(wData, hData);
    std::string infoScreenSize = std::to_string((int)_screenSize.getX());
    infoScreenSize.append("x");
    infoScreenSize.append(std::to_string((int)_screenSize.getY()));
    _logger.logInfo("Screen size:", infoScreenSize);

    _openGLContext = SDL_GL_CreateContext(_window.get());
    SDL_GL_MakeCurrent(_window.get(), _openGLContext);

    if (!gladLoadGL()) {
      _logger.logErrorLine("Failed to initialise glad.");
      return -1;
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

  ShaderProgram NovelRenderingService::loadShaders(std::string vertexFilePath, std::string fragmentFilePath) {

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
      throw EXIT_FAILURE;
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
      throw EXIT_FAILURE;
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
      throw EXIT_FAILURE;
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

  int NovelRenderingService::initialiseRendering(int displayNumber, const std::string& windowTitle) {
    if (!initialiseRenderPipeline(displayNumber, windowTitle)) {
      _logger.logErrorLine("Apologies, something went wrong. Reason: SDL could not initialise.");
      throw EXIT_FAILURE;
    }

    SDL_GetWindowSize(getWindow().get(), &_winWidth, &_winHeight);

    return 0;
  }

  std::string NovelRenderingService::getWindowTitle() const {
    return SDL_GetWindowTitle(getWindow().get());
  }
  void NovelRenderingService::setWindowTitle(const std::string& value) {
    return SDL_SetWindowTitle(getWindow().get(), value.c_str());
  }

  void NovelRenderingService::tearDown() const {
    glDeleteProgram(_basicFillRectProgram.shaderProgramId);
    glDeleteProgram(_texturedRectProgram.shaderProgramId);
    SDL_DestroyWindow(getWindow().get());
    SDL_Quit();
  }

  void NovelRenderingService::beginFrame() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  }

  void NovelRenderingService::endFrame() const {
    SDL_GL_SwapWindow(_window.get());
  }

  NovelImageRect* NovelRenderingService::getImageRect(const std::string& filePath,
    const NovelCommonArgs& args,
    const RGBAConfig& colourTint) {
    return new NovelImageRect(_layeringService, args, _texturedRectProgram, getCamera(), filePath, colourTint);
  }

  NovelTextRect* NovelRenderingService::getTextRect(const RGBAConfig& colourConfig,
    float fontSize,
    const std::string& fontFilePath,
    const NovelCommonArgs& args) {
    return new NovelTextRect(_layeringService, args, _fontProgram, getCamera(), fontSize, fontFilePath, colourConfig);
  }

  std::shared_ptr<SDL_Window> NovelRenderingService::getWindow() const {
    return _window;
  }

  NovelRenderingService::NovelRenderingService(NovelLayeringService* layeringService) : _logger(NovelLoggingService(NovelUtilities::CONSOLE_LOG_GFX)), _layeringService(layeringService), _cameraObjectRenderUbo(std::function<GLuint()>([] {
    GLuint tempHandle;
    glGenBuffers(1, &tempHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, tempHandle);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraBlock), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, tempHandle, 0, sizeof(CameraBlock));
    return tempHandle;
    })),
    _camera(std::make_unique<NovelCamera>()) {}

    NovelBasicFillRect* NovelRenderingService::getBasicFillRect(const RGBAConfig& colourConfig, const NovelCommonArgs& args) {
      return new NovelBasicFillRect(_layeringService, colourConfig, args, _basicFillRectProgram, getCamera());
    }

    GeoVector<float> NovelRenderingService::getScreenSize() const {
      return _screenSize;
    }

    NovelCamera* NovelRenderingService::getCamera() const
    {
      return _camera.get();
    }

    void NovelRenderingService::bindCameraUboForProgram(GLuint shaderProgramId) {
      GLuint uboIndex = glGetUniformBlockIndex(shaderProgramId, "finalViewMatrixBuffer");
      glUniformBlockBinding(shaderProgramId, uboIndex, 0);

      //TODO: This is what handles buffering part of the data into the UBO, but this is only partial.
      //GLuint handle = _cameraObjectRenderUbo.getActual();
      //glBindBuffer(GL_UNIFORM_BUFFER, handle);
      //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraBlock), &_cameraBlockObj.getActual());
      //glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    //NovelRenderingService::CameraBlock NovelRenderingService::generateCameraBlock() {
    //  return CameraBlock(_camera.getCameraUboMatrix().getUnderlyingMatrix());
    //}
}
