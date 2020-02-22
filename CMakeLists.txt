cmake_minimum_required(VERSION 3.13)

project(NovelRT VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/Wall /WX)
else()
    add_compile_options(-pedantic -pedantic-error -Wall -Wextra -Weverything -Werror)
endif()

include_directories(include)

add_subdirectory(src)

if (NOT NOVELRT_SKIP_SAMPLES)
  add_subdirectory(samples)
endif()

if (NOT NOVELRT_SKIP_DOCUMENTATION)
  add_subdirectory(doxygen)
endif()

if (NOT NOVELRT_SKIP_TESTS)
  add_subdirectory(tests)
endif()
