# Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT).
# See LICENCE.md in the repository root for more information.

#[=======================================================================[.rst:
NovelRTBuildSystem
-------------

This module defines the core interface for the NovelRT build system.
#]=======================================================================]

block(SCOPE_FOR POLICIES)
cmake_policy(VERSION 3.29..3.31)

#[=======================================================================[.rst:
.. command:: NovelRTBuildSystem_DeclareModule

  This function declares a NovelRT module, containing some code which should
  compile and link against the engine.
#]=======================================================================]
function(NovelRTBuildSystem_DeclareModule moduleKind moduleName)

  #cmake_language(DEFER DIRECTORY ${CMAKE_SOURCE_DIR} CANCEL_CALL novelRTDeferredGeneration)
  #cmake_language(DEFER DIRECTORY ${CMAKE_SOURCE_DIR} ID novelRTDeferredGeneration CALL __NovelRTBuildSystem_includeModules)

  string(TOLOWER "${moduleName}" moduleNameLower)
  set(savedDetailsPropertyName "_NovelRTBuildSystem_declaredModules_${moduleNameLower}")

  cmake_parse_arguments(PARSE_ARGV 1 "declareModule" "" "" "DEPENDS;OPTIONAL_DEPENDS;SOURCES;HEADERS;RESOURCES;COMPILE_FEATURES;COMPILE_DEFINITIONS;COMPILE_OPTIONS;INCLUDE_DIRECTORIES;LINK_LIBRARIES")
  set(dependsClosure ${declareModule_DEPENDS} ${declareModule_OPTIONAL_DEPENDS})
  set_property(GLOBAL PROPERTY ${savedDetailsPropertyName}_DEPENDS ${dependsClosure})
  set_property(GLOBAL PROPERTY ${savedDetailsPropertyName}_OPTIONAL_DEPENDS ${declareModule_OPTIONAL_DEPENDS})

  set(validKinds "LIBRARY;EXECUTABLE")
  if(NOT (moduleKind IN_LIST validKinds))
    message(SEND_ERROR
      "Module must either be a LIBRARY or EXECUTABLE: "
      "${moduleName}")
    return()
  endif()

  foreach(kind SOURCES HEADERS RESOURCES)
    cmake_parse_arguments(declareModule_${kind} "" "" "BASE_DIRS;INTERFACE;PUBLIC;PRIVATE" ${declareModule_${kind}})
  endforeach()

  string(REGEX REPLACE "::" "-" cmakeSafeName ${moduleName})
  if(moduleKind STREQUAL "LIBRARY")
    # N.B. Static is important here so that target_link_libraries works as expected
    add_library(${cmakeSafeName} STATIC)
    add_library(${moduleName} ALIAS ${cmakeSafeName})
  elseif(moduleKind STREQUAL "EXECUTABLE")
    add_executable(${cmakeSafeName})
    add_executable(${moduleName} ALIAS ${cmakeSafeName})

    # N.B. This is needed so that Windows gets the correct DLLs in dev.
    add_custom_command(TARGET ${cmakeSafeName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${cmakeSafeName}> $<TARGET_RUNTIME_DLLS:${cmakeSafeName}>
      COMMAND_EXPAND_LISTS)
  endif()

  if(PROJECT_IS_TOP_LEVEL)
    find_program(NovelRTBuildSystem_clangTidy NAMES clang-tidy DOC "Location of clang-tidy used in debug builds.")
    if(NovelRTBuildSystem_clangTidy)
      set(clangTidyCommandLine ${NovelRTBuildSystem_clangTidy} --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy)
    endif()
  endif()

  set_target_properties(${cmakecmakeSafeName} PROPERTIES
    EXPORT_NAME ${cmakeSafeName}
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
    CXX_CLANG_TIDY "$<$<CONFIG:Debug>:${clangTidyCommandLine}>")

  target_compile_features(${cmakeSafeName} PUBLIC cxx_std_17)
  target_compile_options(${cmakeSafeName} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wabi>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>

    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->)

  # CMake doesn't like static libraries with no sources, so we add the dependencies as private sources to silence it.
  # This PROBABLY leads to some duplication but fortunately the linker is really good at de-duplicating code
  foreach(depends IN LISTS declareModule_DEPENDS)
    target_sources(${cmakeSafeName} PRIVATE $<TARGET_OBJECTS:${depends}>)
  endforeach()
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    target_sources(${cmakeSafeName} PRIVATE $<$<TARGET_EXISTS:${depends}>:$<TARGET_OBJECTS:${depends}>>)
  endforeach()

  set(resx ${declareModule_RESOURCES_INTERFACE} ${declareModule_RESOURCES_PUBLIC} ${declareModule_RESOURCES_PRIVATE})
  foreach(file IN LISTS resx)
    configure_file(${file} ${file} COPYONLY)
  endforeach()

  list(TRANSFORM declareModule_RESOURCES_INTERFACE REPLACE "^(.+)$" "$<BUILD_INTERFACE:\\1>")
  list(TRANSFORM declareModule_RESOURCES_PUBLIC REPLACE "^(.+)$" "$<BUILD_INTERFACE:\\1>")

  target_sources(${cmakeSafeName}
    INTERFACE ${declareModule_SOURCES_INTERFACE} ${declareModule_RESOURCES_INTERFACE}
    PUBLIC ${declareModule_SOURCES_PUBLIC} ${declareModule_RESOURCES_PUBLIC}
    PRIVATE ${declareModule_SOURCES_PRIVATE} ${declareModule_RESOURCES_PRIVATE}

    INTERFACE FILE_SET interface_headers
    TYPE HEADERS
    BASE_DIRS include ${declareModule_HEADERS_BASE_DIRS}
    FILES ${declareModule_HEADERS_INTERFACE}
    PUBLIC FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include ${declareModule_HEADERS_BASE_DIRS}
    FILES ${declareModule_HEADERS_PUBLIC}
    PRIVATE FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS include ${declareModule_HEADERS_BASE_DIRS}
    FILES ${declareModule_HEADERS_PRIVATE})

  target_link_libraries(${cmakeSafeName} PUBLIC ${declareModule_DEPENDS})
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    target_link_libraries(${cmakeSafeName} PUBLIC $<$<TARGET_EXISTS:${depends}>:${depends}>)
  endforeach()

  if(declareModule_COMPILE_FEATURES)
    target_compile_features(${cmakeSafeName} ${declareModule_COMPILE_FEATURES})
  endif()
  if(declareModule_COMPILE_DEFINITIONS)
    target_compile_definitions(${cmakeSafeName} ${declareModule_COMPILE_DEFINITIONS})
  endif()
  if(declareModule_COMPILE_OPTIONS)
    target_compile_options(${cmakeSafeName} ${declareModule_COMPILE_OPTIONS})
  endif()
  if(declareModule_INCLUDE_DIRECTORIES)
    target_include_directories(${cmakeSafeName} ${declareModule_INCLUDE_DIRECTORIES})
  endif()
  if(declareModule_LINK_LIBRARIES)
    target_link_libraries(${cmakeSafeName} ${declareModule_LINK_LIBRARIES})
  endif()

  install(
    TARGETS ${cmakeSafeName}
    EXPORT NovelRTConfig
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    FILE_SET interface_headers DESTINATION include
    FILE_SET public_headers DESTINATION include)
endfunction()

endblock()
