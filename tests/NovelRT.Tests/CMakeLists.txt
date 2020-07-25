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
    GTest::GTest
    GTest::Main
    GMock::GMock
    GMock::Main
)

gtest_discover_tests(Engine_Tests)
