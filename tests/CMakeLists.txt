find_package(GTest CONFIG REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wno-global-constructors -Wno-weak-vtables)
endif()

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
  NovelRTInterop
)

add_executable(NovelRTTests ${NOVELRT_TESTS_HEADERS} ${NOVELRT_TESTS_SOURCES})
add_dependencies(NovelRTTests NovelRTTestsDependencies)

target_link_libraries(NovelRTTests ${NOVELRT_TESTS_LINK_LIBRARIES})

enable_testing()
add_test(NAME NovelRTTests COMMAND NovelRTTests --gtest_output=xml)

add_custom_command(TARGET NovelRTTests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/NovelRTTests.txt
)

set_property(TARGET NovelRTTests PROPERTY
  BINARY_OUTDIR $<TARGET_FILE_DIR:NovelRTTests>
)

# NovelRTTests.Dependencies

set(NOVELRT_TESTS_DEPENDENCIES_INPUTS
  $<TARGET_FILE:NovelRT>
  ${CMAKE_BINARY_DIR}/src/NovelRTDotNet.txt
  ${CMAKE_BINARY_DIR}/src/NovelRTResources.txt
  ${CMAKE_BINARY_DIR}/src/NovelRTInteropResources.txt
)

set(NOVELRT_TESTS_DEPENDENCIES_OUTPUTS
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRT.txt
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTDotNet.txt
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTResources.txt
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTInteropResources.txt
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTTestsDependencies.txt
)

add_custom_command(OUTPUT ${NOVELRT_TESTS_DEPENDENCIES_OUTPUTS}
  COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:NovelRT> $<TARGET_GENEX_EVAL:NovelRTTests,$<TARGET_PROPERTY:NovelRTTests,BINARY_OUTDIR>>
  COMMAND ${CMAKE_COMMAND} -E touch ${NOVELRT_TESTS_DEPENDENCIES_OUTPUTS}
  DEPENDS ${NOVELRT_TESTS_DEPENDENCIES_INPUTS}
)

add_custom_target(NovelRTTestsDependencies ALL DEPENDS ${NOVELRT_TESTS_DEPENDENCIES_OUTPUTS})
