find_package(GTest)
include(GoogleTest)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Tests
  DEPENDS
    NovelRT::Graphics
    NovelRT::Graphics::Vulkan
    NovelRT::Windowing
    NovelRT::ResourceManagement
    NovelRT::Timing
    NovelRT::Ecs

  SOURCES
    Ecs/CatalogueTest.cpp
    Ecs/ComponentBufferMemoryContainerTest.cpp
    Ecs/ComponentBufferTest.cpp
    Ecs/ComponentCacheTest.cpp
    Ecs/ComponentViewTest.cpp
    Ecs/EntityCacheTest.cpp
    Ecs/EntityGraphViewTest.cpp
    Ecs/LinkedEntityListViewTest.cpp
    Ecs/SparseSetTest.cpp
    Ecs/SystemSchedulerTest.cpp
    Ecs/SparseSetMemoryContainerTest.cpp

    Maths/GeoBoundsTest.cpp
    Maths/GeoMatrix4x4Test.cpp
    Maths/GeoVector2Test.cpp
    Maths/GeoVector3Test.cpp
    Maths/GeoVector4Test.cpp
    Maths/QuadTreeTest.cpp
    Maths/UtilitiesTest.cpp

    # TODO: Needs porting from LegacySrc
    # Persistence/ChapterTest.cpp

    Utilities/BitCastTest.cpp
    Utilities/BitflagsTest.cpp
    Utilities/EventTest.cpp

    main.cpp

  LINK_LIBRARIES
    PUBLIC
      GTest::gtest_main
)

gtest_discover_tests(NovelRT-Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/"
  DISCOVERY_MODE PRE_TEST)
