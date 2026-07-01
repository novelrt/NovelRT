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

  cmake_parse_arguments(PARSE_ARGV 2 "declareModule" "MACOSX_BUNDLE;WIN32_EXECUTABLE" "" "DEPENDS;OPTIONAL_DEPENDS;SOURCES;HEADERS;RESOURCES;COMPILE_FEATURES;COMPILE_DEFINITIONS;COMPILE_OPTIONS;PRECOMPILE_HEADERS;INCLUDE_DIRECTORIES;LINK_LIBRARIES")
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
  string(REGEX REPLACE "::" "." macosx_bundle_identifier ${moduleName})
  string(TOLOWER "${macosx_bundle_identifier}" macosx_bundle_identifier)
  if(moduleKind STREQUAL "LIBRARY")
    # N.B. Static is important here so that target_link_libraries works as expected
    add_library(${cmakeSafeName} STATIC)
    add_library(${moduleName} ALIAS ${cmakeSafeName})

    set(moduleOutputName ${cmakeSafeName})

  elseif(moduleKind STREQUAL "EXECUTABLE")
    add_executable(${cmakeSafeName})
    add_executable(${moduleName} ALIAS ${cmakeSafeName})

    string(REGEX REPLACE "^.+::(.*)$" "\\1" moduleOutputName ${moduleName})

    # N.B. This is needed so that Windows gets the correct DLLs in dev.
    add_custom_command(TARGET ${cmakeSafeName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${cmakeSafeName}> $<TARGET_RUNTIME_DLLS:${cmakeSafeName}>
      COMMAND_EXPAND_LISTS)

    add_custom_command(TARGET ${cmakeSafeName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/LICENCE-DIST.md
      $<TARGET_FILE_DIR:${cmakeSafeName}>/LICENCE-DIST.md)
  endif()

  if(NOVELRT_CLANG_TIDY)
    find_program(NOVELRT_CLANG_TIDY_PATH NAMES clang-tidy HINTS "${NOVELRT_CLANG_TIDY_PATH}" DOC "Location of clang-tidy used in debug builds.")
    if(NOVELRT_CLANG_TIDY_PATH)
      set(clangTidyCommandLine ${NOVELRT_CLANG_TIDY_PATH} --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy -p ${CMAKE_BINARY_DIR})
    endif()
  endif()

  set_target_properties(${cmakeSafeName} PROPERTIES
    EXPORT_NAME ${moduleName}
    OUTPUT_NAME ${moduleOutputName}
		COMPILE_PDB_NAME ${moduleOutputName}
		PDB_NAME ${moduleOutputName}
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
    CXX_CLANG_TIDY "${clangTidyCommandLine}"
    MACOSX_BUNDLE "${declareModule_MACOSX_BUNDLE}"
    MACOSX_BUNDLE_NAME "${moduleName}"
    MACOSX_BUNDLE_VERSION "${PROJECT_VERSION}"
    MACOSX_BUNDLE_COPYRIGHT "NovelRT Contributors"
    MACOSX_BUNDLE_GUI_IDENTIFIER "${macosx_bundle_identifier}"
    WIN32_EXECUTABLE "${declareModule_WIN32_EXECUTABLE}")

  target_compile_features(${cmakeSafeName} PUBLIC cxx_std_20)
  # FIXME: When upgrading to CMake 3.30 change these to $<CXX_COMPILER_FRONTEND_VARIANT:xxx>
  target_compile_options(${cmakeSafeName} PRIVATE
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wall>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wall>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wabi>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Werror>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wextra>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wpedantic>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-pedantic-errors>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>:-Wconversion>

    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-Wall>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-Werror>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-Wextra>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-Wpedantic>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-pedantic-errors>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},Clang>:-Wconversion>

    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<BOOL:${NOVELRT_ENABLE_UBSAN}>>:-fsanitize=undefined>

    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>:/W4>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>:/WX>
    $<$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>:/permissive->

    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug,RelWithDebInfo>>:-fstandalone-debug>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug,RelWithDebInfo>>:-fno-eliminate-unused-debug-types>)

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
    # Copy the resources to their output directory. In the future we may do something more advanced like compiling shaders.
    add_custom_command(
      OUTPUT ${file}
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${file}" "$<TARGET_FILE_DIR:${cmakeSafeName}>/${file}"
      MAIN_DEPENDENCY ${file}
      COMMENT "Copying resource ${file}"
      DEPENDS_EXPLICIT_ONLY)
  endforeach()

  list(TRANSFORM declareModule_RESOURCES_INTERFACE REPLACE "^(.+)$" "$<BUILD_INTERFACE:\\1>")
  list(TRANSFORM declareModule_RESOURCES_PUBLIC REPLACE "^(.+)$" "$<BUILD_INTERFACE:\\1>")

  target_sources(${cmakeSafeName}
    INTERFACE ${declareModule_SOURCES_INTERFACE} ${declareModule_RESOURCES_INTERFACE}
    PUBLIC ${declareModule_SOURCES_PUBLIC} ${declareModule_RESOURCES_PUBLIC}
    PRIVATE ${declareModule_SOURCES_PRIVATE} ${declareModule_HEADERS_PRIVATE} ${declareModule_RESOURCES_PRIVATE}

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
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${declareModule_HEADERS_BASE_DIRS}
    FILES ${declareModule_HEADERS_PRIVATE}

    INTERFACE FILE_SET interface_resources
    TYPE HEADERS
    BASE_DIRS Resources ${declareModule_RESOURCES_BASE_DIRS}
    FILES ${declareModule_RESOURCES_INTERFACE}
    PUBLIC FILE_SET public_resources
    TYPE HEADERS
    BASE_DIRS Resources ${declareModule_RESOURCES_BASE_DIRS}
    FILES ${declareModule_RESOURCES_PUBLIC}
    PRIVATE FILE_SET private_resources
    TYPE HEADERS
    BASE_DIRS Resources ${declareModule_RESOURCES_BASE_DIRS}
    FILES ${declareModule_RESOURCES_PRIVATE})

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
  if(declareModule_PRECOMPILE_HEADERS)
    target_precompile_headers(${cmakeSafeName} ${declareModule_PRECOMPILE_HEADERS})
  endif()
  if(declareModule_INCLUDE_DIRECTORIES)
    target_include_directories(${cmakeSafeName} ${declareModule_INCLUDE_DIRECTORIES})
  endif()
  if(declareModule_LINK_LIBRARIES)
    target_link_libraries(${cmakeSafeName} ${declareModule_LINK_LIBRARIES})
  endif()

  if(NOVELRT_INSTALL)
    if(APPLE AND declareModule_MACOSX_BUNDLE)
      install(CODE "include(BundleUtilities)\nfixup_bundle(\"$<TARGET_BUNDLE_DIR:${cmakeSafeName}>\" \"\" \"$<INSTALL_PREFIX>/lib;$<INSTALL_PREFIX>/bin\")")
    endif()

    install(
      TARGETS ${cmakeSafeName}
      EXPORT NovelRTConfig
      ARCHIVE DESTINATION lib
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin
      BUNDLE DESTINATION apps
      FILE_SET interface_headers DESTINATION include
      FILE_SET public_headers DESTINATION include

      FILE_SET interface_resources DESTINATION bin/Resources
      FILE_SET public_resources DESTINATION bin/Resources)

    if(WIN32 AND moduleKind STREQUAL "EXECUTABLE")
      install(FILES $<TARGET_PDB_FILE:${cmakeSafeName}> DESTINATION bin OPTIONAL)
    endif()
  endif()
endfunction()

endblock()
