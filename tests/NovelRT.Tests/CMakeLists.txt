find_package(GTest)
include(GoogleTest)

set(SOURCES
  Ecs/CatalogueTest.cpp
  Ecs/ComponentBufferMemoryContainerTest.cpp
  Ecs/ComponentBufferTest.cpp
  Ecs/ComponentCacheTest.cpp
  Ecs/ComponentViewTest.cpp
  Ecs/ConfiguratorTest.cpp
  Ecs/EntityCacheTest.cpp
  Ecs/EntityGraphViewTest.cpp
  Ecs/LinkedEntityListViewTest.cpp
  Ecs/SparseSetTest.cpp
  Ecs/SystemSchedulerTest.cpp
  Ecs/SparseSetMemoryContainerTest.cpp

  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/NovelRTInteropUtilsTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtCatalogueTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtComponentBufferMemoryContainerTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtComponentCacheTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtEntityCacheTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtSparseSetMemoryContainerTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Ecs/NrtSystemSchedulerTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/GeoBoundsTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/GeoMatrix4x4Test.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/GeoVector2FTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/GeoVector3FTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/GeoVector4FTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/QuadTreePointTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Maths/QuadTreeTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/ResourceManagement/BinaryMemberMetadataTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/SceneGraph/NovelRTSceneNodeTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Timing/NovelRTTimestampTest.cpp>

  Maths/GeoBoundsTest.cpp
  Maths/GeoMatrix4x4Test.cpp
  Maths/GeoVector2Test.cpp
  Maths/GeoVector3Test.cpp
  Maths/GeoVector4Test.cpp
  Maths/QuadTreeTest.cpp
  Maths/UtilitiesTest.cpp

  Persistence/ChapterTest.cpp

  SceneGraph/SceneNodeTest.cpp

  Timing/TimestampTest.cpp

  Utilities/BitCastTest.cpp
  Utilities/BitflagsTest.cpp
  Utilities/EventTest.cpp

  main.cpp
)


include(${PROJECT_SOURCE_DIR}/cmake/CopyBuildProducts.cmake)

if(APPLE)
  add_executable(Engine_Tests MACOSX_BUNDLE ${SOURCES})
  set_target_properties(Engine_Tests 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.Engine_Tests
      MACOS_BUNDLE_BUNDLE_NAME Engine_Tests
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(Engine_Tests ${SOURCES})
endif()

target_compile_options(Engine_Tests
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
  set_property(TARGET Engine_Tests PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  get_target_property(opts Engine_Tests COMPILE_OPTIONS)
endif()

if(NOVELRT_BUILD_INTEROP)
  copy_runtime_dependencies(Engine_Tests
    DEPENDENCY Engine
    DEPENDENCY Interop
  )
else()
  copy_runtime_dependencies(Engine_Tests
    DEPENDENCY Engine
  )
endif()

if(APPLE)
  copy_runtime_dependencies(Engine_Tests
    LIBRARY GTest::gtest_main
    LIBRARY GTest::gtest
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
endif()

target_link_libraries(Engine_Tests
  PUBLIC
    Engine
    $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop>
    GTest::gtest_main
) 

gtest_discover_tests(Engine_Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/"
  DISCOVERY_MODE PRE_TEST)

