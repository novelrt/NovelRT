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
find_package(Vorbis ${NOVELRT_VORBIS_VERSION} REQUIRED)
find_package(Microsoft.GSL ${NOVELRT_GSL_VERSION} REQUIRED)
find_package(Vulkan ${NOVELRT_VULKAN_VERSION} REQUIRED)

set(SOURCES
  Animation/SpriteAnimator.cpp

  Audio/AudioService.cpp

  DebugService.cpp

  DotNet/RuntimeService.cpp

  Ecs/Catalogue.cpp
  Ecs/ComponentBufferMemoryContainer.cpp
  Ecs/ComponentCache.cpp
  Ecs/EntityCache.cpp
  Ecs/SparseSetMemoryContainer.cpp
  Ecs/SystemScheduler.cpp
  Ecs/UnsafeComponentView.cpp

  Experimental/Graphics/Vulkan/VulkanGraphicsDevice.cpp
  Experimental/Windowing/Glfw/GlfwWindowingDevice.cpp

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

add_library(Engine SHARED ${SOURCES})
add_dependencies(Engine Dotnet)

set_property(TARGET Engine PROPERTY OUTPUT_NAME "NovelRT")

if(WIN32)
  set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

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
    Microsoft.GSL::Microsoft.GSL
    Vulkan::Vulkan
)

if(WIN32)
  target_link_libraries(Engine
    PUBLIC
      Winmm
  )

  if(NOVELRT_INCLUDE_CONAN_PATHS)
    add_custom_command(TARGET Engine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_BINARY_DIR}/thirdparty
      $<TARGET_FILE_DIR:Engine>)
  endif()
endif()
