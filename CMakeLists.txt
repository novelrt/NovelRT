cmake_minimum_required(VERSION 3.13)
project(NovelRT)

set(CMAKE_CXX_STANDARD 17)

add_executable(NovelRT nanovg/nanovg.c main.cpp NovelObject.cpp NovelObject.h GeoVector.cpp GeoVector.h NovelBasicFillRect.cpp NovelBasicFillRect.h RGBAConfig.cpp RGBAConfig.h)