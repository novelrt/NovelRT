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

  Interop/GeoVector2FTest.cpp
  Interop/GeoVector3FTest.cpp  
  Interop/GeoVector4FTest.cpp
  Interop/QuadTreeTTest.cpp

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

gtest_discover_tests(Engine_Tests)
