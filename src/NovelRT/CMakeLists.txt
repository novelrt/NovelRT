find_package(BZip2 ${NOVELRT_BZIP2_VERSION} REQUIRED)
find_package(Dotnet ${NOVELRT_DOTNET_VERSION} REQUIRED)
find_package(flac ${NOVELRT_FLAC_VERSION} REQUIRED)
find_package(Freetype ${NOVELRT_FREETYPE_VERSION} REQUIRED)
find_package(glad ${NOVELRT_GLAD_VERSION} REQUIRED
  COMPONENTS
    REPRODUCIBLE
    PROFILE core
    SPEC gl
    API gl=4.0,gles2=3.0
)
find_package(glfw3 ${NOVELRT_GLFW_VERSION} REQUIRED)
find_package(glm ${NOVELRT_GLM_VERSION} REQUIRED)
find_package(Ogg ${NOVELRT_OGG_VERSION} REQUIRED)
find_package(OpenAL ${NOVELRT_OPENAL_VERSION} REQUIRED)
find_package(Opus ${NOVELRT_Opus_VERSION} REQUIRED)
find_package(PNG ${NOVELRT_PNG_VERSION} REQUIRED)
find_package(SndFile ${NOVELRT_SNDFILE_VERISON} REQUIRED)
find_package(spdlog ${NOVELRT_SPDLOG_VERSION} REQUIRED)
find_package(Vorbis ${NOVELRT_Vorbis_VERSION} REQUIRED)

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

  Ink/InkService.cpp
  Ink/Story.cpp

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

add_library(Engine SHARED ${ENGINE_SOURCES})
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
      /MP
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
    BZip2::BZip2
    CoreCLR::nethost
    FLAC::FLAC
    Freetype::Freetype
    glad::glad
    glfw::glfw
    glm::glm
    Ogg::Ogg
    OpenAL::OpenAL
    Opus::Opus
    PNG::PNG
    SndFile::SndFile
    spdlog::spdlog
    Vorbis::Vorbis
)

if(WIN32)
  target_link_libraries(Engine
    PUBLIC
      Winmm
  )
endif()
