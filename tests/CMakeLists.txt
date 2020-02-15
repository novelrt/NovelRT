find_package(GTest CONFIG REQUIRED)

set(NOVELRT_TESTS_HEADERS)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_TESTS_HEADERS})

file(GLOB_RECURSE NOVELRT_TESTS_SOURCES CONFIGURE_DEPENDS NovelRT.Tests/*.cpp)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_TESTS_SOURCES})

set(NOVELRT_TESTS_LINK_LIBRARIES
  GTest::gtest
  GTest::gtest_main
  GTest::gmock
  GTest::gmock_main
  NovelRT
)

add_executable(NovelRTTests ${NOVELRT_TESTS_HEADERS} ${NOVELRT_TESTS_SOURCES})
target_link_libraries(NovelRTTests ${NOVELRT_TESTS_LINK_LIBRARIES})

enable_testing()
add_test(NAME NovelRTTests COMMAND NovelRTTests)
