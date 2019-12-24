cmake_minimum_required(VERSION 3.13)

project(NovelRT VERSION 0.0.1)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

set(NOVELRT_FONTS
  src/Gayathri-Regular.ttf
  src/Raleway-Regular.ttf
)

set(NOVELRT_IMAGES
  novel-chan.png
)

set(NOVELRT_SCRIPTS
  src/avg.lua
)

set(NOVELRT_SHADERS
  src/BasicFragmentShader.glsl
  src/BasicVertexShader.glsl
  src/FontFragmentShader.glsl
  src/FontVertexShader.glsl
  src/TexturedFragmentShader.glsl
  src/TexturedVertexShader.glsl
)

set(NOVELRT_RESOURCES
  ${NOVELRT_FONTS}
  ${NOVELRT_IMAGES}
  ${NOVELRT_SCRIPTS}
  ${NOVELRT_SHADERS}
)

file(COPY ${NOVELRT_RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm") #TODO: check if the OPENGL_VERSION flag is actually still needed with the new setup
    file(GLOB CORECLR lib/CoreCLR/LinuxARM32/*)
    add_compile_definitions(OPENGL_VERSION=2)
else()
    add_compile_definitions(OPENGL_VERSION=3)
endif()

file(COPY ${CORECLR} DESTINATION lib/CoreCLR/Active)

find_package(Freetype REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# lua doesn't provide native cmake support
find_path(LUA_INCLUDE_DIR lua.h)
include_directories(${LUA_INCLUDE_DIR})

find_library(LUA_LIBRARY lua)
link_libraries(${LUA_LIBRARY})

find_package(Doxygen QUIET)
include_directories(include)

set(NOVELRT_HEADERS
  include/NovelRT/Transform.h
  include/NovelRT/Maths/GeoBounds.h
  include/NovelRT/Maths/GeoVector.h
  include/NovelRT/Graphics/GraphicsCharacterRenderData.h
  include/NovelRT/Input/KeyCode.h
  include/NovelRT/Utilities/Lazy.h
  include/NovelRT/Audio/AudioService.h
  include/NovelRT/Graphics/BasicFillRect.h
  include/NovelRT/Input/BasicInteractionRect.h
  include/NovelRT/DebugService.h
  include/NovelRT/Graphics/ImageRect.h
  include/NovelRT/Input/InteractionObject.h
  include/NovelRT/Input/InteractionService.h
  include/NovelRT/LoggingService.h
  include/NovelRT/Graphics/RenderingService.h
  include/NovelRT/Graphics/RenderObject.h
  include/NovelRT/Utilities/Misc.h
  include/NovelRT/NovelRunner.h
  include/NovelRT/Timing/StepTimer.h
  include/NovelRT/Graphics/TextRect.h
  include/NovelRT/Graphics/RGBAConfig.h
  include/NovelRT/Graphics/Camera.h
  include/NovelRT/Maths/GeoMatrix4.h
  include/NovelRT/Graphics/CameraViewChangedEventArgs.h
  include/NovelRT/Graphics/ShaderProgram.h
  include/NovelRT/Graphics/CameraBlock.h
  include/NovelRT/Windowing/WindowingService.h
  include/NovelRT/Input/KeyState.h
  include/NovelRT/WorldObject.h
  include/NovelRT.h)

set(NOVELRT_SOURCES
  src/NovelRT/Transform.cpp
  src/NovelRT/Maths/GeoBounds.cpp
  src/NovelRT/Audio/AudioService.cpp
  src/NovelRT/Graphics/BasicFillRect.cpp
  src/NovelRT/Input/BasicInteractionRect.cpp
  src/NovelRT/DebugService.cpp
  src/NovelRT/Graphics/ImageRect.cpp
  src/NovelRT/Input/InteractionObject.cpp
  src/NovelRT/Input/InteractionService.cpp
  src/NovelRT/LoggingService.cpp
  src/NovelRT/Graphics/RenderingService.cpp
  src/NovelRT/Graphics/RenderObject.cpp
  src/NovelRT/NovelRunner.cpp
  src/NovelRT/Timing/StepTimer.cpp
  src/NovelRT/Graphics/TextRect.cpp
  src/NovelRT/Graphics/RGBAConfig.cpp
  src/NovelRT/Graphics/Camera.cpp
  src/NovelRT/Windowing/WindowingService.cpp
  src/NovelRT/WorldObject.cpp)

set(NOVELRT_LINK_LIBRARIES
  Freetype::Freetype
  glad::glad
  glm
  SDL2::SDL2-static
  SDL2::SDL2_image
  SDL2::SDL2_mixer
  SDL2::SDL2main
  spdlog::spdlog
)

if(NOT WIN32)
    set(NOVELRT_LINK_LIBRARIES
      ${NOVELRT_LINK_LIBRARIES}
      m
    )
endif()

set(NOVELRT_EXECUTABLE_HEADERS
  ${NOVELRT_HEADERS}
)

set(NOVELRT_EXECUTABLE_SOURCES
  src/main.cpp
)

set(NOVELRT_EXECUTABLE_LINK_LIBRARIES
  libNovelRT
)

add_executable(NovelRT ${NOVELRT_EXECUTABLE_HEADERS} ${NOVELRT_EXECUTABLE_SOURCES})
target_link_libraries(NovelRT ${NOVELRT_EXECUTABLE_LINK_LIBRARIES})

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(NOVELRT_LIBRARY_HEADERS
  ${NOVELRT_HEADERS}
  #include/NovelRT/NovelRT-C/NovelRunner_C.h
)

set(NOVELRT_LIBRARY_SOURCES
  ${NOVELRT_SOURCES}
  #src/NovelRunner_C.cpp
)

set(NOVELRT_LIBRARY_LINK_LIBRARIES
  ${NOVELRT_LINK_LIBRARIES}
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND false)
  target_compile_options(NovelRT
    PRIVATE
      -Werror
      -Wall
      -Wextra
      -Wduplicate-enum

      -Wlong-long

      -Wnull-dereference

      -Wdouble-promotion
      -Wshadow
      -Wformat=2
      -Wno-error=unused-parameter
      -Wno-error=unused-variable
  )

  set(SANITIZE_CODE ON)

  # Enable various sanitizer extensions
  if (${SANITIZE_CODE})
    message("Enabling code sanitizer extensions.")

    target_compile_options(NovelRT
      PRIVATE
      -fsanitize=undefined
      -fsanitize=address
      -fsanitize=shift
      -fsanitize=shift-exponent
      -fsanitize=shift-base
      -fsanitize=integer-divide-by-zero
      -fsanitize=unreachable
      -fsanitize=vla-bound
      -fsanitize=null
      -fsanitize=return
      -fsanitize=signed-integer-overflow
      -fsanitize=bounds
      -fsanitize=alignment
      -fsanitize=object-size
      -fsanitize=float-divide-by-zero
      -fsanitize=float-cast-overflow
      -fsanitize=nonnull-attribute
      -fsanitize=returns-nonnull-attribute
      -fsanitize=bool
      -fsanitize=enum
      -fsanitize=vptr
      -fno-sanitize-recover=all
    )

    target_link_options(NovelRT
      PRIVATE
        -fsanitize=undefined
        -fsanitize=address
        -fsanitize=shift
        -fsanitize=shift-exponent
        -fsanitize=shift-base
        -fsanitize=integer-divide-by-zero
        -fsanitize=unreachable
        -fsanitize=vla-bound
        -fsanitize=null
        -fsanitize=return
        -fsanitize=signed-integer-overflow
        -fsanitize=bounds
        -fsanitize=alignment
        -fsanitize=object-size
        -fsanitize=float-divide-by-zero
        -fsanitize=float-cast-overflow
        -fsanitize=nonnull-attribute
        -fsanitize=returns-nonnull-attribute
        -fsanitize=bool
        -fsanitize=enum
        -fsanitize=vptr
    )
  endif ()
endif ()

add_library(libNovelRT SHARED ${NOVELRT_LIBRARY_HEADERS} ${NOVELRT_LIBRARY_SOURCES})
target_link_libraries(libNovelRT ${NOVELRT_LIBRARY_LINK_LIBRARIES})

# Docs

if (DOXYGEN_FOUND)
  set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/src)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
  set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
  set(DOXYGEN_FAKE_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/__index.html)
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(DOXYFILE_OUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)

  set(DOCS_IMAGES
    novel-chan_doxy.png
  )
  set(DOCS_RESOURCES
    ${DOCS_IMAGES}
  )

  #Replace variables inside @@ with the current values
  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
  file(COPY ${DOCS_RESOURCES} DESTINATION ${DOXYGEN_OUTPUT_DIR})

  add_custom_command(OUTPUT
                       ${DOXYGEN_INDEX_FILE}
                       ${DOXYGEN_FAKE_INDEX_FILE}
                     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                     MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                     COMMENT "Generating docs")

  add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
endif (DOXYGEN_FOUND)
