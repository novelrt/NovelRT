find_package(GTest ${NOVELRT_GTEST_VERSION} REQUIRED
  COMPONENTS gtest_main
)

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

  Interop/NovelRTInteropUtilsTest.cpp
  Interop/Ecs/NrtCatalogueTest.cpp
  Interop/Ecs/NrtComponentBufferMemoryContainerTest.cpp
  Interop/Ecs/NrtComponentCacheTest.cpp
  Interop/Ecs/NrtEntityCacheTest.cpp
  Interop/Ecs/NrtSparseSetMemoryContainerTest.cpp
  Interop/Ecs/NrtSystemSchedulerTest.cpp
  Interop/Maths/GeoBoundsTest.cpp
  Interop/Maths/GeoMatrix4x4Test.cpp
  Interop/Maths/GeoVector2FTest.cpp
  Interop/Maths/GeoVector3FTest.cpp
  Interop/Maths/GeoVector4FTest.cpp
  Interop/Maths/QuadTreePointTest.cpp
  Interop/Maths/QuadTreeTest.cpp
  Interop/SceneGraph/NovelRTSceneNodeTest.cpp
  Interop/Timing/NovelRTTimestampTest.cpp

  Maths/GeoBoundsTest.cpp
  Maths/GeoMatrix4x4Test.cpp
  Maths/GeoVector2Test.cpp
  Maths/GeoVector3Test.cpp
  Maths/GeoVector4Test.cpp
  Maths/QuadTreeTest.cpp
  Maths/UtilitiesTest.cpp

  SceneGraph/SceneNodeTest.cpp

  Timing/TimestampTest.cpp

  Utilities/BitflagsTest.cpp
  Utilities/EventTest.cpp

  main.cpp
 )

add_executable(Engine_Tests ${SOURCES})
target_link_libraries(Engine_Tests
  PUBLIC
    Engine
    Interop
    GTest::gtest
    GTest::gtest_main
)

copy_build_products(Engine_Tests
  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>

  DEPENDENCY Interop
  TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)

gtest_discover_tests(Engine_Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/")
