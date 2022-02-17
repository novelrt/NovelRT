set(SOURCES
  NrtInteropErrorHandling.cpp
  NrtLoggingService.cpp

  Audio/NrtAudioService.cpp

  Ecs/NrtCatalogue.cpp
  Ecs/NrtComponentBufferMemoryContainer.cpp
  Ecs/NrtComponentCache.cpp
  Ecs/NrtEntityCache.cpp
  Ecs/NrtEntityIdVector.cpp
  Ecs/NrtSparseSetMemoryContainer.cpp
  Ecs/NrtSystemScheduler.cpp
  Ecs/NrtUnsafeComponentView.cpp

  Ecs/Audio/NrtAudioSystem.cpp
  Ecs/Audio/NrtAudioEmitterComponent.cpp
  Ecs/Audio/NrtAudioEmitterStateComponent.cpp

  Graphics/NrtRGBAColour.cpp

  Maths/NrtGeoBounds.cpp
  Maths/NrtGeoMatrix4x4F.cpp
  Maths/NrtGeoVector2F.cpp
  Maths/NrtGeoVector3F.cpp
  Maths/NrtGeoVector4F.cpp
  Maths/NrtQuadTree.cpp
  Maths/NrtQuadTreePoint.cpp

  PluginManagement/NrtDefaultPluginSelector.cpp
  PluginManagement/NrtIGraphicsPluginProvider.cpp
  PluginManagement/NrtIInputPluginProvider.cpp
  PluginManagement/NrtIResourceManagementPluginProvider.cpp
  PluginManagement/NrtIWindowingPluginProvider.cpp

  SceneGraph/NrtQuadTreeNode.cpp
  SceneGraph/NrtQuadTreeScenePoint.cpp
  SceneGraph/NrtScene.cpp
  SceneGraph/NrtSceneNode.cpp
  SceneGraph/NrtSceneNodeBreadthFirstIterator.cpp
  SceneGraph/NrtSceneNodeDepthFirstIterator.cpp

  Timing/NrtStepTimer.cpp
  Timing/NrtTimestamp.cpp

  Utilities/NrtMisc.cpp
)

add_library(Interop SHARED ${SOURCES})
add_dependencies(Interop Engine)

set_property(TARGET Interop PROPERTY OUTPUT_NAME "NovelRT.Interop")

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
