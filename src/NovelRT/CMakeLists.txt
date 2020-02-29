find_package(freetype CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(libpng CONFIG REQUIRED)
find_package(LibSndFile CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

if(NOVELRT_SUPPORT_DOTNET)
  find_package(nethost REQUIRED)
endif()

if(NOVELRT_SUPPORT_LUA)
  find_package(Lua REQUIRED)
endif()

include(CopyDependencyOutputs)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${LUA_INCLUDE_DIR}
  $<$<BOOL:${NOVELRT_SUPPORT_DOTNET}>:${NETHOST_INCLUDE_DIR}>
)

set(NovelRT_SRCS
Audio/AudioService.cpp

$<$<BOOL:${NOVELRT_SUPPORT_DOTNET}>:DotNet/RuntimeService.cpp>

Graphics/BasicFillRect.cpp Graphics/Camera.cpp Graphics/FontSet.cpp
Graphics/ImageRect.cpp Graphics/RenderingService.cpp Graphics/RenderObject.cpp
Graphics/RGBAConfig.cpp Graphics/TextRect.cpp Graphics/Texture.cpp

Input/BasicInteractionRect.cpp Input/InteractionObject.cpp
Input/InteractionService.cpp

Maths/GeoBounds.cpp Maths/QuadTree.cpp

Timing/StepTimer.cpp

Utilities/Misc.cpp

Windowing/WindowingService.cpp

DebugService.cpp LoggingService.cpp NovelRunner.cpp Transform.cpp WorldObject.cpp
)

add_library(NovelRT SHARED ${NovelRT_SRCS})

target_compile_definitions(NovelRT
  PUBLIC
    $<$<BOOL:${NOVELRT_SUPPORT_DOTNET}>:NOVELRT_SUPPORT_DOTNET>
)

add_dependencies(NovelRT NovelRT_DotNet NovelRT_Resources)

target_include_directories(NovelRT
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(NovelRT
  PUBLIC
    freetype
    glad::glad
    glfw
    glm
    OpenAL::OpenAL
    png
    spdlog::spdlog_header_only
    "$<$<BOOL:${NOVELRT_SUPPORT_LUA}>:${LUA_LIBRARIES}>"
    "$<$<BOOL:${NOVELRT_SUPPORT_DOTNET}>:${NETHOST_LIBRARIES}>"
    "$<IF:$<BOOL:${WIN32}>,sndfile-shared,sndfile-static>"
    "$<IF:$<BOOL:${WIN32}>,,m;stdc++fs>"
)

if(WIN32)
  set_target_properties(NovelRT
    PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

copy_dependency_outputs(NovelRT NovelRT_Resources _resource_output_files_list)
add_dependency_outputs(NovelRT ${_resource_output_files_list})
install_dependency_outputs(
  FILES ${_resource_output_files_list}
  DESTINATION bin)

mark_as_advanced(_resource_output_files_list)

if(NOVELRT_SUPPORT_DOTNET)
  copy_dependency_outputs(NovelRT NovelRT_DotNet _dotnet_output_files_list)
  add_dependency_outputs(NovelRT ${_dotnet_output_files_list})
  install_dependency_outputs(
    FILES ${_dotnet_output_files_list}
    DESTINATION bin)

  mark_as_advanced(_resource_output_files_list)
endif()

if(NOVELRT_GENERATOR_IS_MULTI_CONFIG)
  add_dependency_outputs(NovelRT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_SHARED_LIBRARY_PREFIX}NovelRT${CMAKE_SHARED_LIBRARY_SUFFIX}")
else()
  add_dependency_outputs(NovelRT "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}NovelRT${CMAKE_SHARED_LIBRARY_SUFFIX}")
endif()

install(
  TARGETS NovelRT
  EXPORT NovelRTRuntime
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

# TODO: figure out if this is required on other platforms...

if(WIN32)
  function(generate_library_install_snippet)
    foreach(install_libraries_config IN LISTS CMAKE_CONFIGURATION_TYPES)
      string(REGEX MATCHALL "." config_characters "${install_libraries_config}")

      set(config_regex "^(")
      foreach(character IN LISTS config_characters)
        string(TOUPPER "${character}" character_uppercase)
        string(TOLOWER "${character}" character_lowercase)
        set(config_regex "${config_regex}[${character_uppercase}${character_lowercase}]")
      endforeach()
      set(config_regex "${config_regex})$")

      string(CONFIGURE
[[@install_libraries_prefix@if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "@config_regex@")
    file(GET_RUNTIME_DEPENDENCIES
         RESOLVED_DEPENDENCIES_VAR novelrt_resolved_dependencies
         LIBRARIES "@CMAKE_CURRENT_BINARY_DIR@/@install_libraries_config@/@CMAKE_SHARED_LIBRARY_PREFIX@NovelRT@CMAKE_SHARED_LIBRARY_SUFFIX@")
    foreach(dependency IN LISTS novelrt_resolved_dependencies)
      file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/@install_libraries_config@/bin" FILES "${dependency}")
    endforeach()]]
        snippet @ONLY)

      list(APPEND install_deps_snippet "${snippet}")
      if(NOT install_libraries_prefix)
        set(install_libraries_prefix "else")
      endif()
    endforeach()

    list(APPEND install_deps_snippet "endif()")
    list(JOIN install_deps_snippet "\r\n  " install_deps_snippet)
    install(CODE "${install_deps_snippet}")
  endfunction()

  generate_library_install_snippet()
endif()
