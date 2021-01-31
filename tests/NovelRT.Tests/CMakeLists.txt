find_package(GTest 1.10.0 REQUIRED
  COMPONENTS
    Main
)
find_package(GMock 1.10.0 REQUIRED
  COMPONENTS
    Main
)

include(GoogleTest)

set(TEST_SOURCES
  Animation/SpriteAnimatorStateTest.cpp

  Ecs/CatalogueTest.cpp
  Ecs/ComponentBufferMemoryContainerTest.cpp
  Ecs/ComponentBufferTest.cpp
  Ecs/ComponentCacheTest.cpp
  Ecs/ComponentViewTest.cpp
  Ecs/EntityCacheTest.cpp
  Ecs/SparseSetTest.cpp
  Ecs/SystemSchedulerTest.cpp
  Ecs/SparseSetMemoryContainerTest.cpp

  Interop/NovelRTInteropUtilsTest.cpp
  Interop/Animation/SpriteAnimatorStateTest.cpp
  Interop/Ecs/NrtCatalogue.cpp
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

  SceneGraph/SceneNodeTest.cpp

  Timing/TimestampTest.cpp

  Utilities/BitflagsTest.cpp
  Utilities/EventTest.cpp

  main.cpp
 )


add_executable(Engine_Tests ${TEST_SOURCES})
target_link_libraries(Engine_Tests
  PUBLIC
    Engine
    Interop
    GTest::GTest
    GTest::Main
    GMock::GMock
    GMock::Main
)

add_custom_command(
  TARGET Engine_Tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Dotnet>
    $<TARGET_FILE_DIR:Engine_Tests>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
  add_custom_command(
    TARGET Engine_Tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_FILE_DIR:Engine_Tests>/dotnet/nethost.dll
      $<TARGET_FILE_DIR:Engine_Tests>
  )
endif()

add_custom_command(
  TARGET Engine_Tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:Engine_Tests>
)

add_custom_command(
  TARGET Engine_Tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    $<TARGET_FILE_DIR:Engine_Tests>
)

gtest_discover_tests(Engine_Tests
  EXTRA_ARGS "--gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/../results/")
