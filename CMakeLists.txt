cmake_minimum_required(VERSION 3.13)
project(NovelRT)

set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-yuri.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(SDL2)

add_executable(NovelRT nanovg/nanovg.c NovelObject.cpp NovelObject.h GeoVector.h NovelBasicFillRect.cpp NovelBasicFillRect.h RGBAConfig.cpp RGBAConfig.h main.cpp NovelRunner.cpp NovelRunner.h NovelImageRect.cpp NovelImageRect.h)



target_link_libraries(NovelRT m GL GLU SDL2)