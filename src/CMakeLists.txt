find_package(Freetype REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(libpng CONFIG REQUIRED)
find_package(LibSndFile CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE NOVELRT_LIB_HEADERS CONFIGURE_DEPENDS ../include/*.h)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_LIB_HEADERS})

file(GLOB_RECURSE NOVELRT_LIB_SOURCES CONFIGURE_DEPENDS NovelRT/*.cpp)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_LIB_SOURCES})

set(NOVELRT_LIB_LINK_LIBRARIES
  Freetype::Freetype
  glad::glad
  glfw
  glm
  OpenAL::OpenAL
  png
  spdlog::spdlog
)

if (WIN32)
  set(NOVELRT_LIB_LINK_LIBRARIES ${NOVELRT_LIB_LINK_LIBRARIES} sndfile-shared)
else()
  set(NOVELRT_LIB_LINK_LIBRARIES ${NOVELRT_LIB_LINK_LIBRARIES} sndfile-static)
endif()

# lua doesn't provide native cmake support

find_path(LUA_INCLUDE_DIRS lua.h)
include_directories(${LUA_INCLUDE_DIRS})

find_library(LUA_LIBRARY NAMES liblua lua)
link_libraries(${LUA_LIBRARY})

# nethost doesn't provide native cmake support

find_path(NETHOST_INCLUDE_DIRS nethost.h)
include_directories(${NETHOST_INCLUDE_DIRS})

find_library(NETHOST_LIBRARY NAMES libnethost nethost)
link_libraries(${NETHOST_LIBRARY})

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
  link_libraries(m)
  link_libraries(stdc++fs)
endif()

add_library(NovelRT SHARED ${NOVELRT_LIB_HEADERS} ${NOVELRT_LIB_SOURCES})
target_link_libraries(NovelRT ${NOVELRT_LIB_LINK_LIBRARIES})

add_custom_command(TARGET NovelRT POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/NovelRT.txt
)

# NovelRT.Resources

file(GLOB_RECURSE NOVELRT_RESOURCE_INPUTS CONFIGURE_DEPENDS
  Resources/Fonts/*.ttf
  Resources/Images/*.png
  Resources/Scripts/*.lua
  Resources/Shaders/*.glsl
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_RESOURCE_INPUTS})

set(NOVELRT_RESOURCE_OUTPUTS
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTResources.txt
)

add_custom_command(OUTPUT ${NOVELRT_RESOURCE_OUTPUTS}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:NovelRT>/Resources
  COMMAND ${CMAKE_COMMAND} -E touch ${NOVELRT_RESOURCE_OUTPUTS}
  DEPENDS ${NOVELRT_RESOURCE_INPUTS}
)

add_custom_target(NovelRTResources ALL DEPENDS ${NOVELRT_RESOURCE_OUTPUTS} SOURCES ${NOVELRT_RESOURCE_INPUTS})

# NovelRT.DotNet

set(NOVELRT_DOTNET_CSPROJ ${CMAKE_CURRENT_SOURCE_DIR}/NovelRT.DotNet/NovelRT.DotNet.csproj)

if("${CMAKE_BUILD_TYPE}" AND NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  set(NOVELRT_DOTNET_CONFIGURATION Release)
else()
  set(NOVELRT_DOTNET_CONFIGURATION Debug)
endif()

file(GLOB_RECURSE NOVELRT_DOTNET_INPUTS CONFIGURE_DEPENDS
  NovelRT.DotNet/*.cs
  NovelRT.DotNet/NovelRT.DotNet.runtimeconfig.json
)
list(FILTER NOVELRT_DOTNET_INPUTS EXCLUDE REGEX NovelRT\.DotNet/obj/.*)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${NOVELRT_DOTNET_INPUTS})

set(NOVELRT_DOTNET_OUTPUTS
  ${CMAKE_CURRENT_BINARY_DIR}/NovelRTDotNet.txt
)

add_custom_command(OUTPUT ${NOVELRT_DOTNET_OUTPUTS}
  COMMAND dotnet build ${NOVELRT_DOTNET_CSPROJ} /p:Configuration=${NOVELRT_DOTNET_CONFIGURATION} /p:OutDir=$<TARGET_FILE_DIR:NovelRT>
  COMMAND ${CMAKE_COMMAND} -E touch ${NOVELRT_DOTNET_OUTPUTS}
  MAIN_DEPENDENCY ${NOVELRT_DOTNET_CSPROJ}
  DEPENDS ${NOVELRT_DOTNET_INPUTS}
)

add_custom_target(NovelRTDotNet ALL DEPENDS ${NOVELRT_DOTNET_OUTPUTS} SOURCES ${NOVELRT_DOTNET_INPUTS})
