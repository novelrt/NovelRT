cmake_minimum_required(VERSION 3.13)
project(NovelRT)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-yuri.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Lua53 REQUIRED)
If(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    add_compile_definitions(OPENGL_VERSION=2)
else()
    add_compile_definitions(OPENGL_VERSION=3)
endif()

if(LINUX)
    include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
endif()


add_subdirectory(lib/SDL2)

add_executable(NovelRT lib/nanovg/nanovg.c src/NovelObject.cpp src/NovelObject.h src/GeoVector.h src/NovelBasicFillRect.cpp src/NovelBasicFillRect.h src/RGBAConfig.cpp src/RGBAConfig.h src/main.cpp src/NovelRunner.cpp src/NovelRunner.h src/NovelImageRect.cpp src/NovelImageRect.h)



target_link_libraries(NovelRT m GL GLU SDL2 ${LUA_LIBRARIES})