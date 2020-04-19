find_package(Freetype 2.10 REQUIRED)
find_package(glad 0.1.33 REQUIRED)
find_package(glm 0.9.9 REQUIRED)
find_package(sndfile 1.0.28 REQUIRED)

set(SOURCES

Animation/SpriteAnimator.cpp

Audio/AudioService.cpp

Graphics/BasicFillRect.cpp Graphics/Camera.cpp Graphics/FontSet.cpp
Graphics/ImageRect.cpp Graphics/RenderingService.cpp Graphics/RenderObject.cpp
Graphics/RGBAConfig.cpp Graphics/TextRect.cpp Graphics/Texture.cpp

Input/BasicInteractionRect.cpp Input/InteractionObject.cpp
Input/InteractionService.cpp

Maths/GeoBounds.cpp Maths/QuadTree.cpp

Timing/StepTimer.cpp

Utilities/Misc.cpp

Windowing/WindowingService.cpp

DebugService.cpp LoggingService.cpp NovelRunner.cpp Transform.cpp
WorldObject.cpp
)

add_library(NovelRT ${SOURCES})

target_compile_features(NovelRT
  PUBLIC
    cxx_std_17
)
target_include_directories(NovelRT
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)
target_link_libraries(NovelRT
  PUBLIC
    Freetype::Freetype
    glad::glad
    glm::glm
)

install(
  TARGETS NovelRT
  EXPORT NovelRT
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY
    "${CMAKE_SOURCE_DIR}/include"
  TYPE INCLUDE
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
)

install(
  EXPORT NovelRT
  NAMESPACE NovelRT::
  DESTINATION lib/NovelRT
)
