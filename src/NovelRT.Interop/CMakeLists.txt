if(NOVELRT_VULKAN_SDK)
  find_dependency(Vulkan REQUIRED)
endif()

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

  Ecs/Graphics/NrtDefaultRenderingSystem.cpp

  Graphics/NrtRGBAColour.cpp

  Maths/NrtGeoBounds.cpp
  Maths/NrtGeoMatrix4x4F.cpp
  Maths/NrtGeoVector2F.cpp
  Maths/NrtGeoVector3F.cpp
  Maths/NrtGeoVector4F.cpp
  Maths/NrtQuadTree.cpp
  Maths/NrtQuadTreePoint.cpp

  ResourceManagement/NrtBinaryMemberMetadata.cpp
  ResourceManagement/NrtBinaryPackage.cpp
  ResourceManagement/NrtFilePathUuidMap.cpp
  ResourceManagement/NrtUint8Vector.cpp
  ResourceManagement/NrtShaderMetadata.cpp
  ResourceManagement/NrtTextureMetadata.cpp
  ResourceManagement/NrtResourceLoader.cpp
  ResourceManagement/NrtUuidFilePathMap.cpp

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

if(GENERATOR_IS_MULTI_CONFIG)
  set_property(TARGET Interop PROPERTY OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT.Interop,NovelRT.Interop-$<CONFIG>>")
else()
  set_property(TARGET Interop PROPERTY OUTPUT_NAME "$<IF:$<CMAKE_BUILD_TYPE:Release>,NovelRT.Interop,NovelRT.Interop-$<CMAKE_BUILD_TYPE>>")
endif()

target_compile_features(Interop PUBLIC cxx_std_17)
target_include_directories(Interop
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(Interop
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4611>
    $<$<CXX_COMPILER_ID:MSVC>:/MP>

    $<$<CXX_COMPILER_ID:GNU>:-pedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-padded>

    $<$<CXX_COMPILER_ID:Clang>:-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-reserved-id-macro>

    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wextra>
    $<$<CXX_COMPILER_ID:AppleClang>:-Werror>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-reserved-id-macro>
)

if(MSVC)
  set_property(TARGET Interop PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  get_target_property(opts Interop COMPILE_OPTIONS)
endif()

target_link_libraries(Interop
  PUBLIC
    Engine)

install(
  TARGETS Interop
  EXPORT NovelRT
  DESTINATION lib
  RUNTIME DESTINATION bin
)
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/NovelRT.Interop/
  DESTINATION include/NovelRT.Interop
  FILES_MATCHING PATTERN "*.h"
)
