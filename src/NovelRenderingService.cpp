// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRenderingService.h"

#include <SDL2/SDL.h>
#include <iostream>

#define GL_GLEXT_PROTOTYPES



#include "GeoVector.h"
#include "NovelBasicFillRect.h"
#include "NovelImageRect.h"
#include <algorithm>
#include <fstream>
#include <sstream>

namespace NovelRT {
bool NovelRenderingService::initializeRenderPipeline(int displayNumber) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    std::cerr << "ERROR: could not initialize sdl2: " << SDL_GetError() << std::endl;
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
      "NovelRTTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
  if (_window == nullptr) {
    std::cerr << "could not create window: " << SDL_GetError() << std::endl;

    return false;
  }

  _screenSize = GeoVector<uint32_t>(static_cast<uint32_t>(glm::round(wData)), static_cast<uint32_t>(glm::round(hData)));
  std::cout << "INFO: Screen size is " << _screenSize.getX() << "x" << _screenSize.getY() << std::endl;

  _openGLContext = SDL_GL_CreateContext(_window.get());
  SDL_GL_MakeCurrent(_window.get(), _openGLContext);

  if (!gladLoadGL()) {
    std::cerr << "ERROR: Failed to initialise glad." << std::endl;
    return -1;
  }

  std::cout << "GL_VERSION : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;



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
    std::cerr << "ERROR: Target Vertex Shader file cannot be opened! Please ensure the path is correct and that the file is not locked." << std::endl;
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
    std::cerr << "ERROR: Target Fragment Shader file cannot be opened! Please ensure the path is correct and that the file is not locked." << std::endl;
    getchar();
    return 0;
  }

  GLint Result = GL_FALSE;
  int infoLogLength;

  // Compile Vertex Shader
  std::cout << "INFO: Compiling shader: " << vertexFilePath << "..." << std::endl;
  char const * vertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(vertexShaderId, 1, &vertexSourcePointer , nullptr);
  glCompileShader(vertexShaderId);

  // Check Vertex Shader
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if ( infoLogLength > 0 ){
    std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
    std::cerr << "ERROR: " << &vertexShaderErrorMessage[0] << std::endl;
  }

  // Compile Fragment Shader
  std::cout << "INFO: Compiling shader: " << fragmentFilePath << "..." << std::endl;
  const char* FragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(fragmentShaderId, 1, &FragmentSourcePointer , nullptr);
  glCompileShader(fragmentShaderId);

  // Check Fragment Shader
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if ( infoLogLength > 0 ){
    std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
    glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
    std::cerr << "ERROR: " << &fragmentShaderErrorMessage[0] << std::endl;
  }

  // Link the program
  std::cout << "INFO: Linking program..." << std::endl;
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
    std::cerr << "ERROR: " << &ProgramErrorMessage[0] << std::endl;
  }

  glDetachShader(programId, vertexShaderId);
  glDetachShader(programId, fragmentShaderId);

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);


  return programId;
}

int NovelRenderingService::initialiseRendering(int displayNumber) {
  if (!initializeRenderPipeline(displayNumber)) {
    std::cerr << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
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
  return new NovelImageRect(_layeringService, startingSize, filePath, args, _texturedRectProgramId, colourTint);
}

NovelTextRect* NovelRenderingService::getTextRect(const RGBAConfig& colourConfig,
                                                  float fontSize,
                                                  const std::string& fontFilePath,
                                                  const NovelCommonArgs& args) {
  return new NovelTextRect(_layeringService, fontSize, fontFilePath, colourConfig, args, _fontProgramId);
}

std::shared_ptr<SDL_Window> NovelRenderingService::getWindow() const {
  return _window;
}

NovelRenderingService::NovelRenderingService(NovelLayeringService* layeringService) : _layeringService(layeringService) {
}

NovelBasicFillRect* NovelRenderingService::getBasicFillRect(const GeoVector<float>& startingSize,
                                                            const RGBAConfig& colourConfig,
                                                            const NovelCommonArgs& args) {
  return new NovelBasicFillRect(_layeringService, startingSize, colourConfig, args, _basicFillRectProgramId);
}

GeoVector<u_int32_t> NovelRenderingService::getScreenSize() const {
  return _screenSize;
}
}