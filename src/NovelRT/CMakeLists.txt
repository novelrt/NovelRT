find_package(Freetype 2.10.1 REQUIRED)
find_package(glad 0.1.30 REQUIRED
  COMPONENTS
    REPRODUCIBLE
    SPEC gl
    PROFILE core
    API gl=4.0,gles2=3.0
)
find_package(spdlog 1.5.0 REQUIRED)
find_package(nethost 3.1.202 REQUIRED)

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
target_compile_features(Engine PUBLIC cxx_std_17)

target_link_libraries(Engine
  PUBLIC
    Freetype::Freetype
    glad
    nethost
)
