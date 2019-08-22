cmake_minimum_required(VERSION 3.13)
project(NovelRT VERSION 0.0.1)
include(GNUInstallDirs)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test-yuri.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB LUA_FILES "src/*.lua")
file(COPY ${LUA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB GLSL_FILES "src/*.glsl")
file(COPY ${GLSL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

add_subdirectory(lib/lua53)

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(NovelRT src/NovelObject.cpp src/NovelObject.h src/NovelInteractionService.h src/NovelLayeringService.cpp  src/GeoVector.h src/NovelBasicFillRect.cpp src/NovelBasicFillRect.h src/RGBAConfig.cpp src/RGBAConfig.h src/main.cpp src/NovelImageRect.cpp src/NovelImageRect.h src/NovelRunner.cpp src/NovelRunner.h src/NovelRenderingService.cpp src/NovelRenderingService.h src/NovelCommonArgs.h  src/NovelRenderObject.cpp src/NovelRenderObject.h src/NovelTextRect.cpp src/NovelTextRect.h src/NovelInteractionService.cpp src/NovelInteractionObject.cpp src/NovelInteractionObject.h src/NovelObjectSortComparison.h src/NovelBasicInteractionRect.cpp src/NovelBasicInteractionRect.h src/GeoBounds.cpp src/GeoBounds.h src/NovelRTMacroUtilities.h)
target_link_libraries(NovelRT m lua glad::glad SDL2::SDL2main SDL2::SDL2-static)



add_library(NovelRTLib SHARED src/NovelInteractionService.h src/NovelLayeringService.cpp src/NovelObject.cpp src/NovelObject.h src/GeoVector.h src/NovelBasicFillRect.cpp src/NovelBasicFillRect.h src/RGBAConfig.cpp src/RGBAConfig.h src/main.cpp src/NovelImageRect.cpp src/NovelImageRect.h src/NovelRunner.cpp src/NovelRunner.h src/NovelRenderingService.cpp src/NovelRenderingService.h src/NovelRunner_C.cpp src/NovelRunner_C.h src/NovelCommonArgs.h src/NovelInteractionService.cpp src/NovelRenderObject.cpp src/NovelRenderObject.h src/NovelTextRect.cpp src/NovelTextRect.h src/NovelInteractionObject.cpp src/NovelInteractionObject.h src/KeyCode.h src/NovelObjectSortComparison.h src/NovelBasicInteractionRect.cpp src/NovelBasicInteractionRect.h src/GeoBounds.cpp src/GeoBounds.h src/NovelRTMacroUtilities.h)
target_link_libraries(NovelRTLib m glew GLM SDL2 lua)
set_target_properties(NovelRTLib PROPERTIES PUBLIC_HEADER include/NovelRTLib_C.h)
install(TARGETS NovelRTLib
        LIBRARY DESTINATION /lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION /usr/include/${PROJECT_NAME})

