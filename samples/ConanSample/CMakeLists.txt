cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

project(NovelRT-ConanSample
  VERSION 0.1.0
  LANGUAGES C
)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(NovelRT REQUIRED)
set(SOURCES
  main.c
)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

add_executable(ConanSample ${SOURCES})
target_link_libraries(ConanSample
  PRIVATE
    NovelRT::NovelRT
)
target_include_directories(ConanSample PRIVATE ${NovelRT_INCLUDE_DIRS})

add_custom_command(TARGET ConanSample POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_BINARY_DIR}/bin
      $<TARGET_FILE_DIR:ConanSample>)

add_custom_command(TARGET ConanSample POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_BINARY_DIR}/../../../Resources
      $<TARGET_FILE_DIR:ConanSample>/Resources)
# add_custom_command(
#   TARGET ConanSample POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#     $<TARGET_FILE_DIR:Resources>
#     $<TARGET_FILE_DIR:ConanSample>/Resources
# )

# add_custom_command(
#   TARGET ConanSample POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#     $<TARGET_FILE_DIR:Engine>
#     $<TARGET_FILE_DIR:ConanSample>
# )

# add_custom_command(
#   TARGET ConanSample POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#     $<TARGET_FILE_DIR:Interop>
#     $<TARGET_FILE_DIR:ConanSample>
# )

