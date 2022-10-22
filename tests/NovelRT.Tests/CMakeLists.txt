include(GoogleTest)
if(NOVELRT_VULKAN_SDK)
  find_dependency(Vulkan REQUIRED)
endif()

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

  Utilities/BitflagsTest.cpp
  Utilities/EventTest.cpp

  main.cpp
)

add_executable(Engine_Tests ${SOURCES})
include(${PROJECT_SOURCE_DIR}/cmake/CopyBuildProducts.cmake)

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
  set_property(TARGET Engine_Tests PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  get_target_property(opts Engine_Tests COMPILE_OPTIONS)
endif()

if(NOVELRT_BUILD_INTEROP)
  copy_build_products(Engine_Tests
    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>

    DEPENDENCY Interop
    TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>
  )
else()
  copy_build_products(Engine_Tests
    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>
  )
endif()

target_link_libraries(Engine_Tests
  PUBLIC
    Engine
    $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop>
    gtest_main
)

gtest_discover_tests(Engine_Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/"
  DISCOVERY_MODE PRE_TEST)

