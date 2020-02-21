find_package(GTest CONFIG REQUIRED)
include(CopyDependencyOutputs)

if (NOT MSVC)
  add_compile_options(-Wno-global-constructors -Wno-missing-prototypes -Wno-weak-vtables)
endif()

set(NovelRT_Tests_SRCS

Animation/SpriteAnimatorStateTest.cpp

Maths/QuadTreeTest.cpp

Utilities/EventTest.cpp

main.cpp)

set(NOVELRT_TESTS_LINK_LIBRARIES
  GTest::gtest
  GTest::gtest_main
  GTest::gmock
  GTest::gmock_main
  NovelRT
)

add_executable(NovelRT_Tests ${NovelRT_Tests_SRCS})
add_dependencies(NovelRT_Tests NovelRT)

target_link_libraries(NovelRT_Tests
  GTest::gtest
  GTest::gtest_main
  GTest::gmock
  GTest::gmock_main
  NovelRT)

copy_dependency_outputs(NovelRT_Tests NovelRT)

add_test(NAME tests COMMAND NovelRT_Tests --gtest_output=xml)
