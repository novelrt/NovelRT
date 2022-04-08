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
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/SceneGraph/NovelRTSceneNodeTest.cpp>
  $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop/Timing/NovelRTTimestampTest.cpp>

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

if(NOVELRT_INCLUDE_CONAN_PATHS AND (WIN32 OR APPLE))
  add_dependencies(EcsPipeline ThirdParty)
  if(NOVELRT_BUILD_INTEROP)
    copy_build_products(EcsPipeline
      DEPENDENCY Engine
      TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>

      DEPENDENCY ThirdParty
      TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>

      DEPENDENCY Interop
      TARGET_LOCATION $<TARGET_FILE_DIR:Engine_Tests>
    )
  else()
    copy_build_products(EcsPipeline
      DEPENDENCY Engine
      TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>

      DEPENDENCY ThirdParty
      TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>
    )
  endif()
else()
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
endif()

target_link_libraries(Engine_Tests
  PUBLIC
    Engine
    $<$<BOOL:${NOVELRT_BUILD_INTEROP}>:Interop>
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(Engine_Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/")
