// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRenderingService.h"

#include <SDL2/SDL.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES

#include "GeoVector.h"
#include "NovelBasicFillRect.h"
#include "NovelImageRect.h"
#include "NovelRTUtilities.h"
#include <algorithm>
#include <fstream>
#include <sstream>

namespace NovelRT {
bool NovelRenderingService::initializeRenderPipeline(int displayNumber) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    _logger.log("Could not initialize sdl2: " + std::string(SDL_GetError()), LogLevel::ERR);
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_DEBUG_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    SDL_DisplayMode displayData;
  SDL_GetCurrentDisplayMode(displayNumber, &displayData);
  _screenScale = (displayData.h * 0.7f) / 1080.0f;

  _logger.log("Screen Scale: " + std::to_string(_screenScale), LogLevel::INFO);


  // create window
  float wData = 1920.0f * _screenScale;
  float hData = 1080.0f * _screenScale;
  _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
      "NovelRTTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
  if (_window == nullptr) {
    _logger.log("Could not create window: " + std::string(SDL_GetError()), LogLevel::ERR);

    return false;
  }
  _openGLContext = SDL_GL_CreateContext(_window.get());
  SDL_GL_MakeCurrent(_window.get(), _openGLContext);

  if (!gladLoadGL()) {
    _logger.log("Failed to initialise glad.", LogLevel::ERR);
    return -1;
  }

  std::string glVersion = (const char*) glGetString(GL_VERSION);
  std::string glShading = (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
  _logger.log("GL_VERSION: " + glVersion, LogLevel::INFO);
  _logger.log("GL_SHADING_LANGUAGE_VERSION: " + glShading, LogLevel::INFO);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _basicFillRectProgramId = loadShaders("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
  _texturedRectProgramId = loadShaders("TexturedVertexShader.glsl", "TexturedFragmentShader.glsl");
  _fontProgramId = loadShaders("FontVertexShader.glsl", "FontFragmentShader.glsl");
  return true;
}

GLuint NovelRenderingService::loadShaders(std::string vertexFilePath , std::string fragmentFilePath){

  // Create the shaders
  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string vertexShaderCode;

  std::ifstream VertexShaderStream(vertexFilePath, std::ios::in);
  if(VertexShaderStream.is_open()){
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    vertexShaderCode = sstr.str();
    VertexShaderStream.close();
  }else{
    _logger.log("Target Vertex Shader file cannot be opened! Please ensure the path is correct and that the file is not locked.", LogLevel::ERR);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string fragmentShaderCode;
  std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
  if(fragmentShaderStream.is_open()){
    std::stringstream stringStream;
    stringStream << fragmentShaderStream.rdbuf();
    fragmentShaderCode = stringStream.str();
    fragmentShaderStream.close();
  }else{
    _logger.log("Target Fragment Shader file cannot be opened! Please ensure the path is correct and that the file is not locked.", LogLevel::ERR);
    getchar();
    return 0;
  }

  GLint Result = GL_FALSE;
  int infoLogLength;

  // Compile Vertex Shader
  std::string vertexInfo = "Compiling shader: " + vertexFilePath;
  _logger.log(vertexInfo, LogLevel::INFO);
  char const * vertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(vertexShaderId, 1, &vertexSourcePointer , nullptr);
  glCompileShader(vertexShaderId);

  // Check Vertex Shader
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if ( infoLogLength > 0 ){
    std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
    _logger.log(std::string(&vertexShaderErrorMessage[0]), LogLevel::ERR);
    }

  // Compile Fragment Shader
  std::string fragmentInfo = "Compiling shader: " + fragmentFilePath;
  _logger.log(fragmentInfo, LogLevel::INFO);
  const char* FragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderId, 1, &FragmentSourcePointer , nullptr);
  glCompileShader(fragmentShaderId);

  // Check Fragment Shader
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if ( infoLogLength > 0 ){
    std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
    _logger.log(std::string(&fragmentShaderErrorMessage[0]), LogLevel::ERR);
  }

  // Link the program
  _logger.log("Linking program...", LogLevel::INFO);
  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);

  // Check the program
  glGetProgramiv(programId, GL_LINK_STATUS, &Result);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if ( infoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(infoLogLength+1);
    glGetProgramInfoLog(programId, infoLogLength, nullptr, &ProgramErrorMessage[0]);
    _logger.log(std::string(&ProgramErrorMessage[0]), LogLevel::ERR);
  }

  glDetachShader(programId, vertexShaderId);
  glDetachShader(programId, fragmentShaderId);

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);


  return programId;
}

int NovelRenderingService::initialiseRendering(int displayNumber) {
  if (!initializeRenderPipeline(displayNumber)) {
    _logger.log("Apologies, something went wrong. Reason: SDL could not initialise.", LogLevel::ERR);
    return 1;
  }

  SDL_GetWindowSize(getWindow().get(), &_winWidth, &_winHeight);

  return 0;
}

void NovelRenderingService::tearDown() const {
  glDeleteProgram(_basicFillRectProgramId);
  glDeleteProgram(_texturedRectProgramId);
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

NovelImageRect* NovelRenderingService::getImageRect(const GeoVector<float>& startingSize,
                                                    std::string_view filePath,
                                                    const NovelCommonArgs& args,
                                                    const RGBAConfig& colourTint) {
  return new NovelImageRect(_layeringService, _screenScale, startingSize, filePath, args, _texturedRectProgramId, colourTint);
}

NovelTextRect* NovelRenderingService::getTextRect(const RGBAConfig& colourConfig,
                                                  float fontSize,
                                                  const std::string& fontFilePath,
                                                  const NovelCommonArgs& args) {
  return new NovelTextRect(_layeringService, fontSize, _screenScale, fontFilePath, colourConfig, args, _fontProgramId);
}

std::shared_ptr<SDL_Window> NovelRenderingService::getWindow() const {
  return _window;
}

NovelRenderingService::NovelRenderingService(NovelLayeringService* layeringService) : _layeringService(layeringService), _logger(NovelUtilities::CONSOLE_LOG_GFX) {
}

NovelBasicFillRect* NovelRenderingService::getBasicFillRect(const GeoVector<float>& startingSize,
                                                            const RGBAConfig& colourConfig,
                                                            const NovelCommonArgs& args) {
  return new NovelBasicFillRect(_layeringService, _screenScale, startingSize, colourConfig, args, _basicFillRectProgramId);
}
float NovelRenderingService::getScreenScale() const {
  return _screenScale;
}
}
