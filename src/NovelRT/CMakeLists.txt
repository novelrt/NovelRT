find_package(Freetype 2.8.1 REQUIRED)
find_package(glad 0.1.30 REQUIRED
  COMPONENTS
    REPRODUCIBLE
    SPEC gl
    PROFILE core
    API gl=4.0,gles2=3.0
)
find_package(GLFW 3.2.1 REQUIRED)
find_package(OpenAL 1.19.1 REQUIRED)
find_package(PNG 1.6.34 REQUIRED)
find_package(Sndfile 1.0.28 REQUIRED)
find_package(spdlog 1.4.2 REQUIRED)

add_library(OpenAL::OpenAL UNKNOWN IMPORTED)
set_target_properties(OpenAL::OpenAL
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${OPENAL_INCLUDE_DIR}"
    IMPORTED_LOCATION "${OPENAL_LIBRARY}"
)

set(ENGINE_SOURCES
  Animation/SpriteAnimator.cpp

  Audio/AudioService.cpp

  DebugService.cpp

  DotNet/RuntimeService.cpp

  Graphics/BasicFillRect.cpp
  Graphics/Camera.cpp
  Graphics/FontSet.cpp
  Graphics/ImageRect.cpp
  Graphics/RenderingService.cpp
  Graphics/RenderObject.cpp
  Graphics/RGBAConfig.cpp
  Graphics/TextRect.cpp
  Graphics/Texture.cpp

  Input/BasicInteractionRect.cpp
  Input/InteractionObject.cpp
  Input/InteractionService.cpp

  LoggingService.cpp

  Maths/GeoBounds.cpp
  Maths/QuadTree.cpp

  NovelRunner.cpp

  Timing/StepTimer.cpp

  Transform.cpp

  Utilities/Misc.cpp

  Windowing/WindowingService.cpp

  WorldObject.cpp
)

add_library(Engine ${ENGINE_SOURCES})
add_dependencies(Engine Dotnet)
target_compile_features(Engine PUBLIC cxx_std_17)
target_include_directories(Engine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
  target_compile_options(Engine
    PRIVATE
      /W4
      /WX
      /wd4611
  )
  get_target_property(opts Engine COMPILE_OPTIONS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-float-equal
      -Wno-padded
  )
else()
  target_compile_options(Engine
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-float-equal
      -Wno-padded
      -Wno-reserved-id-macro
  )
endif()

target_link_libraries(Engine
  PUBLIC
    CoreCLR::nethost
    Freetype::Freetype
    Glad::GLAD
    GLFW::GLFW3
    OpenAL::OpenAL
    PNG::PNG
    Sndfile::sndfile
    spdlog::spdlog
)
