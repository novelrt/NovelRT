cmake_minimum_required(VERSION 3.13)
project(NovelRT VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-yuri.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB LUA_FILES "src/*.lua")
file(COPY ${LUA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

If(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    file(GLOB CORECLR lib/CoreCLR/LinuxARM32/*)
    add_compile_definitions(OPENGL_VERSION=2)
else()
    add_compile_definitions(OPENGL_VERSION=3)
endif()

file(COPY ${CORECLR} DESTINATION lib/CoreCLR/Active)

if(LINUX)
    #include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
endif()


add_subdirectory(lib/SDL2)
add_subdirectory(lib/nanovg)
add_subdirectory(lib/lua53)

add_library(NovelRT SHARED src/NovelObject.cpp src/NovelObject.h src/GeoVector.h src/NovelBasicFillRect.cpp src/NovelBasicFillRect.h src/RGBAConfig.cpp src/RGBAConfig.h src/main.cpp src/NovelRunner.cpp src/NovelRunner.h src/NovelImageRect.cpp src/NovelImageRect.h src/NovelRTAPI.h src/NovelRTAPI.cpp)

target_link_libraries(NovelRT m GL GLU SDL2 nanovg lua)