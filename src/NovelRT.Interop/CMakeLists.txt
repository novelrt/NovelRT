set(INTEROP_SOURCES
  NrtInteropErrorHandlingInternal.cpp
  NrtInteropUtils.cpp
  NrtLoggingService.cpp
  NrtNovelRunner.cpp
  NrtTransform.cpp
  NrtDebugService.cpp

  Animation/NrtSpriteAnimatorFrame.cpp
  Animation/NrtSpriteAnimatorState.cpp
  Animation/NrtSpriteAnimator.cpp

  Audio/NrtAudioService.cpp

  DotNet/NrtRuntimeService.cpp
  Ink/NrtInkService.cpp
  Ink/NrtStory.cpp

  Graphics/NrtBasicFillRect.cpp
  Graphics/NrtCamera.cpp
  Graphics/NrtFontSet.cpp
  Graphics/NrtImageRect.cpp
  Graphics/NrtRenderingService.cpp
  Graphics/NrtRGBAConfig.cpp
  Graphics/NrtTextRect.cpp
  Graphics/NrtTexture.cpp

  Input/NrtBasicInteractionRect.cpp
  Input/NrtInteractionService.cpp
  Input/NrtKeyStateFrameChangeLog.cpp

  Maths/NrtGeoMatrix4x4F.cpp
  Maths/NrtGeoBounds.cpp
  Maths/NrtGeoVector2F.cpp
  Maths/NrtGeoVector3F.cpp
  Maths/NrtGeoVector4F.cpp
  Maths/NrtQuadTree.cpp
  Maths/NrtQuadTreePoint.cpp

  SceneGraph/NrtSceneNode.cpp
  SceneGraph/NrtSceneNodeBreadthFirstIterator.cpp
  SceneGraph/NrtSceneNodeDepthFirstIterator.cpp
  SceneGraph/NrtScene.cpp
  SceneGraph/NrtRenderObjectNode.cpp
  SceneGraph/NrtQuadTreeScenePoint.cpp
  SceneGraph/NrtQuadTreeNode.cpp

  Timing/NrtTimestamp.cpp
  Timing/NrtStepTimer.cpp

  Utilities/NrtMisc.cpp

  Windowing/NrtWindowingService.cpp
)

add_library(Interop SHARED ${INTEROP_SOURCES})
add_dependencies(Interop Engine)
target_compile_features(Interop PUBLIC cxx_std_17)
target_include_directories(Interop
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


if(MSVC)
  target_compile_options(Interop
    PRIVATE
      /W4
      /WX
      /wd4611
      /MP
  )
  get_target_property(opts Interop COMPILE_OPTIONS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Interop
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
  target_compile_options(Interop
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

target_link_libraries(Interop
  PUBLIC
    Engine)
