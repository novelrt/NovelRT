cmake_minimum_required(VERSION 3.13)
project(NovelRT)

set(CMAKE_CXX_STANDARD 17)


add_executable(NovelRT nanovg/nanovg.c NovelObject.cpp NovelBasicFillRect.cpp RGBAConfig.cpp main.cpp)

target_link_libraries(NovelRT m GL GLU SDL2)