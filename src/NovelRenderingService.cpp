//
// Created by matth on 19/12/2018.
//

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
bool NovelRenderingService::initializeRenderPipeline(const int displayNumber) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    std::cerr << "could not initialize sdl2: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_DisplayMode displayData;
  SDL_GetCurrentDisplayMode(displayNumber, &displayData);
  _screenScale = (displayData.h * 0.7f) / 1080.0f;

  std::cout << _screenScale << std::endl;


  // create window
  float wData = 1920.0f * _screenScale;
  float hData = 1080.0f * _screenScale;
  _window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
      "NovelRTTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      wData, hData, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
  if (_window == nullptr) {
    std::cerr << "could not create window: " << SDL_GetError() << std::endl;

    return false;
  }
  _openGLContext = SDL_GL_CreateContext(_window.get());
  SDL_GL_MakeCurrent(_window.get(), _openGLContext);
  if (!gladLoadGL()) {
    fprintf(stderr, "Failed to initialize glad\n");
    return -1;
  }

  std::cout << "GL_VERSION : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  _programID = LoadShaders("BasicVertexShader.glsl", "BasicFragmentShader.glsl");
  return true;
}

GLuint NovelRenderingService::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if(VertexShaderStream.is_open()){
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
  }else{
    printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if(FragmentShaderStream.is_open()){
    std::stringstream sstr;
    sstr << FragmentShaderStream.rdbuf();
    FragmentShaderCode = sstr.str();
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}

int NovelRenderingService::initialiseRendering(const int displayNumber) {
  if (!initializeRenderPipeline(displayNumber)) {
    std::cerr << "Apologies, something went wrong. Reason: SDL could not initialise." << std::endl;
    return 1;
  }

  SDL_GetWindowSize(getWindow().get(), &_winWidth, &_winHeight);
  _frameBufferWidth = _winWidth;

  return 0;
}

void NovelRenderingService::tearDown() const {
  SDL_DestroyWindow(getWindow().get());
  SDL_Quit();
}

void NovelRenderingService::beginFrame() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glUseProgram(_programID);
}

void NovelRenderingService::endFrame() const {
  SDL_GL_SwapWindow(_window.get());
}

NovelImageRect* NovelRenderingService::getImageRect(const std::string_view filePath, const NovelCommonArgs& args) {
  return new NovelImageRect(_layeringService, _screenScale, filePath, args);
}

std::shared_ptr<SDL_Window> NovelRenderingService::getWindow() const {
  return _window;
}

NovelRenderingService::NovelRenderingService(NovelLayeringService* layeringService) : _layeringService(layeringService) {
}

NovelBasicFillRect* NovelRenderingService::getBasicFillRect(const GeoVector<float>& startingSize,
                                                            const RGBAConfig& colourConfig,
                                                            const NovelCommonArgs& args) {
  return new NovelBasicFillRect(_layeringService, _screenScale, startingSize, colourConfig, args);
}

float NovelRenderingService::getScreenScale() const {
  return _screenScale;
}
}