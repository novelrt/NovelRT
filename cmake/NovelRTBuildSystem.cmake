# Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT).
# See LICENCE.md in the repository root for more information.

#[=======================================================================[.rst:
NovelRTBuildSystem
-------------

This module defines the core interface for the NovelRT build system.
#]=======================================================================]

block(SCOPE_FOR POLICIES)
cmake_policy(VERSION 3.29..3.31)

define_property(TARGET PROPERTY NOVELRT_DYNAMIC_LIBRARIES)
define_property(TARGET PROPERTY NOVELRT_RESOURCES)
define_property(TARGET PROPERTY NOVELRT_RESOURCES_DESTINATIONS)

#[=======================================================================[.rst:
.. command:: NovelRTBuildSystem_DeclareModule

  This function declares a NovelRT module, containing some code which should
  compile and link against the engine.
#]=======================================================================]
function(NovelRTBuildSystem_DeclareModule moduleKind moduleName)

  cmake_parse_arguments(PARSE_ARGV 2 "declareModule" "MACOSX_BUNDLE;WIN32_EXECUTABLE" "" "DEPENDS;OPTIONAL_DEPENDS;SOURCES;HEADERS;RESOURCES;COMPILE_FEATURES;COMPILE_DEFINITIONS;COMPILE_OPTIONS;PRECOMPILE_HEADERS;INCLUDE_DIRECTORIES;LINK_LIBRARIES;DYNAMIC_LIBRARIES")

  set(validKinds "LIBRARY;EXECUTABLE")
  if(NOT (moduleKind IN_LIST validKinds))
    message(SEND_ERROR
      "Module must either be a LIBRARY or EXECUTABLE: "
      "${moduleName}")
    return()
  endif()

  string(REGEX REPLACE "::" "-" cmakeSafeName ${moduleName})
  string(REGEX REPLACE "::" "." macosxBundleIdentifier ${moduleName})
  string(TOLOWER "${macosx_bundle_identifier}" macosxBundleIdentifier)
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
    if(WIN32)
      add_custom_command(TARGET ${cmakeSafeName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${cmakeSafeName}> $<TARGET_RUNTIME_DLLS:${cmakeSafeName}>
        COMMAND_EXPAND_LISTS)
    endif()
  endif()

  if(declareModule_DYNAMIC_LIBRARIES)
    set(filepaths)
    foreach(library IN LISTS declareModule_DYNAMIC_LIBRARIES)
      list(APPEND filepaths "$<PATH:ABSOLUTE_PATH,NORMALIZE,${library},${CMAKE_CURRENT_SOURCE_DIR}>")
    endforeach()

    file(GENERATE
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/NovelRT_DynamicLibraries.local.txt"
      CONTENT "${filepaths}")
  endif()
  file(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/NovelRT_DynamicLibraries.paths.txt"
    CONTENT "$<LIST:REMOVE_DUPLICATES,$<GENEX_EVAL:$<TARGET_PROPERTY:NOVELRT_DYNAMIC_LIBRARIES>>>"
    TARGET ${cmakeSafeName})

  if(NOVELRT_CLANG_TIDY)
    find_program(NOVELRT_CLANG_TIDY_PATH NAMES clang-tidy HINTS "${NOVELRT_CLANG_TIDY_PATH}" DOC "Location of clang-tidy used in debug builds.")
    if(NOVELRT_CLANG_TIDY_PATH)
      set(clangTidyCommandLine ${NOVELRT_CLANG_TIDY_PATH} --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy -p ${CMAKE_BINARY_DIR})
    endif()
  endif()

  set_target_properties(${cmakeSafeName} PROPERTIES
    COMPILE_PDB_NAME "${moduleOutputName}"
    CXX_CLANG_TIDY "${clangTidyCommandLine}"
    EXPORT_NAME "${moduleName}"
    LINKER_LANGUAGE CXX
    MACOSX_BUNDLE "${declareModule_MACOSX_BUNDLE}"
    MACOSX_BUNDLE_COPYRIGHT "Copyright (C) NovelRT Contributors"
    MACOSX_BUNDLE_GUI_IDENTIFIER "${macosxBundleIdentifier}"
    MACOSX_BUNDLE_NAME "${moduleName}"
    MACOSX_BUNDLE_VERSION "${PROJECT_VERSION}"
    OUTPUT_NAME "${moduleOutputName}"
    PDB_NAME "${moduleOutputName}"
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
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
    target_sources(${cmakeSafeName} PRIVATE
      $<TARGET_OBJECTS:${depends}>
      $<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES>>)
  endforeach()
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    target_sources(${cmakeSafeName} PRIVATE
        $<$<TARGET_EXISTS:${depends}>:$<TARGET_OBJECTS:${depends}>>
        $<$<TARGET_EXISTS:${depends}>:$<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES>>>)
  endforeach()

  foreach(file IN LISTS declareModule_HEADERS)
    cmake_path(GET file PARENT_PATH location)
    string(REGEX REPLACE "^include/" "" location "${location}")
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES MACOSX_PACKAGE_LOCATION "Headers/${location}")
  endforeach()

  set(dynamicLibs)
  if(declareModule_DYNAMIC_LIBRARIES)
    list(APPEND dynamicLibs "${CMAKE_CURRENT_BINARY_DIR}/NovelRT_DynamicLibraries.local.txt")
  endif()
  foreach(depends IN LISTS declareModule_DEPENDS)
    list(APPEND dynamicLibs $<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_DYNAMIC_LIBRARIES>>)
  endforeach()
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    list(APPEND dynamicLibs $<$<TARGET_EXISTS:${depends}>:$<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_DYNAMIC_LIBRARIES>>>)
  endforeach()
  list(REMOVE_DUPLICATES dynamicLibs)
  set_target_properties(${cmakeSafeName} PROPERTIES NOVELRT_DYNAMIC_LIBRARIES "${dynamicLibs}")

  set(localResources)
  set(resourceClosure)
  set(resourceDestinations)
  set(isDestinationArgument OFF)
  foreach(keyword IN LISTS declareModule_RESOURCES)

    if(keyword STREQUAL "DESTINATION")
      set(isDestinationArgument ON)
    elseif(isDestinationArgument)
      set(isDestinationArgument OFF)

      list(POP_BACK resourceDestinations)
      list(APPEND resourceDestinations "${keyword}")
    else()
      string(GENEX_STRIP "${keyword}" resource)
      cmake_path(GET resource PARENT_PATH location)

      list(APPEND localResources "${keyword}")
      list(APPEND resourceClosure "$<PATH:ABSOLUTE_PATH,NORMALIZE,${keyword},${CMAKE_CURRENT_SOURCE_DIR}>")
      list(APPEND resourceDestinations "${location}")
    endif()
  endforeach()
  foreach(depends IN LISTS declareModule_DEPENDS)
    list(APPEND resourceClosure $<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES>>)
    list(APPEND resourceDestinations $<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES_DESTINATIONS>>)
  endforeach()
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    list(APPEND resourceClosure $<$<TARGET_EXISTS:${depends}>:$<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES>>>)
    list(APPEND resourceDestinations $<$<TARGET_EXISTS:${depends}>:$<GENEX_EVAL:$<TARGET_PROPERTY:${depends},NOVELRT_RESOURCES_DESTINATIONS>>>)
  endforeach()

  set_target_properties(${cmakeSafeName} PROPERTIES
    NOVELRT_RESOURCES "${resourceClosure}"
    NOVELRT_RESOURCES_DESTINATIONS "${resourceDestinations}")

  target_sources(${cmakeSafeName}
    PRIVATE ${declareModule_SOURCES} ${declareModule_HEADERS} ${localResources}

    PUBLIC FILE_SET HEADERS
    BASE_DIRS include
    FILES ${declareModule_HEADERS})

  target_link_libraries(${cmakeSafeName} PUBLIC ${declareModule_DEPENDS})
  foreach(depends IN LISTS declareModule_OPTIONAL_DEPENDS)
    target_link_libraries(${cmakeSafeName} PUBLIC $<TARGET_NAME_IF_EXISTS:${depends}>)
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

  set(resourcesStr "cmake_policy(PUSH)\n")
  string(APPEND resourcesStr [[  cmake_policy(SET CMP0007 NEW)]] "\n"
                             [[  set(resources "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES>>")]] "\n"
                             [[  set(destinations "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES_DESTINATIONS>>")]] "\n"
                             [[  list(LENGTH resources resourceCount)]] "\n"
                             [[  if("${resourceCount}" GREATER "0")]] "\n"
                             [[    math(EXPR resourceCount "${resourceCount} - 1")]] "\n"
                             [[    foreach(index RANGE "${resourceCount}")]] "\n"
                             [[      list(GET resources "${index}" resource)]] "\n"
                             [[      list(GET destinations "${index}" destination)]] "\n"
                             [[      if(NOT ("${resource}" STREQUAL "" OR "${destination}" STREQUAL ""))]] "\n"
                             [[        file(COPY "${resource}" DESTINATION "$<TARGET_FILE_DIR:]] "${cmakeSafeName}" [[>/${destination}" USE_SOURCE_PERMISSIONS)]] "\n"
                             [[      endif()]] "\n"
                             [[    endforeach()]] "\n"
                             [[  endif()]] "\n"
                             [[  cmake_policy(POP)]])
  file(GENERATE OUTPUT "NovelRT_CopyResources.cmake" CONTENT "${resourcesStr}")

  add_custom_command(TARGET ${cmakeSafeName} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/NovelRT_CopyResources.cmake"
    COMMAND_EXPAND_LISTS)

  if(NOVELRT_INSTALL)
    if(APPLE AND declareModule_MACOSX_BUNDLE)
      set(fixupStr "include(BundleUtilities)\n")
      string(APPEND fixupStr [[  file(READ "]] "${CMAKE_CURRENT_BINARY_DIR}/NovelRT_DynamicLibraries.paths.txt" [[" dynamicLibPaths)]] "\n"
                             [[  set(dynamicLibs)]] "\n"
                             [[  foreach(dynamicLibPath IN LISTS dynamicLibPaths)]] "\n"
                             [[    if(EXISTS "${dynamicLibPath}")]] "\n"
                             [[      file(READ "${dynamicLibPath}" libs)]] "\n"
                             [[      list(APPEND dynamicLibs ${libs})]] "\n"
                             [[    endif()]] "\n"
                             [[  endforeach()]] "\n"
                             [[  list(REMOVE_DUPLICATES dynamicLibs)]] "\n"
                             [[  list(FILTER dynamicLibs EXCLUDE REGEX "^$")]] "\n"
                             [[  list(FILTER dynamicLibs EXCLUDE REGEX "\.xcframework$")]] "\n"
                             [[  list(REMOVE_DUPLICATES dynamicLibs)]] "\n"
                             [[  file(INSTALL DESTINATION "$<TARGET_BUNDLE_CONTENT_DIR:]] "${cmakeSafeName}" [[>/Frameworks" TYPE FILE FILES ${dynamicLibs} USE_SOURCE_PERMISSIONS FOLLOW_SYMLINK_CHAIN)]] "\n"
                             [[  set(installedDynamicLibs)]] "\n"
                             [[  foreach(dynamicLibPath IN LISTS dynamicLibs)]] "\n"
                             [[    get_filename_component(dynamicLibName "${dynamicLibPath}" NAME)]] "\n"
                             [[    list(APPEND installedDynamicLibs "$<TARGET_BUNDLE_CONTENT_DIR:]] "${cmakeSafeName}" [[>/Frameworks/${dynamicLibName}")]] "\n"
                             [[  endforeach()]] "\n"
                             [[  fixup_bundle("$<TARGET_BUNDLE_DIR:]] "${cmakeSafeName}" [[>" "${installedDynamicLibs}" "$<INSTALL_PREFIX>/lib;$<INSTALL_PREFIX>/bin")]])
      install(CODE "${fixupStr}")

      set(resourcesStr "cmake_policy(PUSH)\n")
      string(APPEND resourcesStr [[  cmake_policy(SET CMP0007 NEW)]] "\n"
                                 [[  set(resources "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES>>")]] "\n"
                                 [[  set(destinations "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES_DESTINATIONS>>")]] "\n"
                                 [[  list(LENGTH resources resourceCount)]] "\n"
                                 [[  if("${resourceCount}" GREATER "0")]] "\n"
                                 [[    math(EXPR resourceCount "${resourceCount} - 1")]] "\n"
                                 [[    foreach(index RANGE "${resourceCount}")]] "\n"
                                 [[      list(GET resources "${index}" resource)]] "\n"
                                 [[      list(GET destinations "${index}" destination)]] "\n"
                                 [[      if(NOT ("${resource}" STREQUAL "" OR "${destination}" STREQUAL ""))]] "\n"
                                 [[        file(INSTALL DESTINATION "$<TARGET_BUNDLE_CONTENT_DIR:]] "${cmakeSafeName}" [[>/${destination}" TYPE FILE FILES "${resource}" USE_SOURCE_PERMISSIONS)]] "\n"
                                 [[      endif()]] "\n"
                                 [[    endforeach()]] "\n"
                                 [[  endif()]] "\n"
                                 [[  cmake_policy(POP)]])
      install(CODE "${resourcesStr}")
    endif()

    set(resourcesStr "cmake_policy(PUSH)\n")
    string(APPEND resourcesStr [[  cmake_policy(SET CMP0007 NEW)]] "\n"
                               [[  set(resources "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES>>")]] "\n"
                               [[  set(destinations "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES_DESTINATIONS>>")]] "\n"
                               [[  list(LENGTH resources resourceCount)]] "\n"
                               [[  if("${resourceCount}" GREATER "0")]] "\n"
                               [[    math(EXPR resourceCount "${resourceCount} - 1")]] "\n"
                               [[    foreach(index RANGE "${resourceCount}")]] "\n"
                               [[      list(GET resources "${index}" resource)]] "\n"
                               [[      list(GET destinations "${index}" destination)]] "\n"
                               [[      if(NOT ("${resource}" STREQUAL "" OR "${destination}" STREQUAL ""))]] "\n"
                               [[        file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/${destination}" TYPE FILE FILES "${resource}" USE_SOURCE_PERMISSIONS)]] "\n"
                               [[      endif()]] "\n"
                               [[    endforeach()]] "\n"
                               [[  endif()]] "\n"
                               [[  cmake_policy(POP)]])
    install(CODE "${resourcesStr}")

    install(
      TARGETS ${cmakeSafeName}
      EXPORT NovelRTConfig
      ARCHIVE DESTINATION lib
      BUNDLE DESTINATION apps
      FILE_SET HEADERS DESTINATION include
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin)

    if(APPLE AND declareModule_MACOSX_BUNDLE)
      set(resourcesStr "cmake_policy(PUSH)\n")
      string(APPEND resourcesStr [[  cmake_policy(SET CMP0007 NEW)]] "\n"
                                 [[  set(destinations "$<GENEX_EVAL:$<TARGET_PROPERTY:]] "${cmakeSafeName}" [[,NOVELRT_RESOURCES_DESTINATIONS>>")]] "\n"
                                 [[  list(LENGTH destinations destinationCount)]] "\n"
                                 [[  if("${destinationCount}" GREATER "0")]] "\n"
                                 [[    math(EXPR destinationCount "${destinationCount} - 1")]] "\n"
                                 [[    foreach(index RANGE "${destinationCount}")]] "\n"
                                 [[      list(GET destinations "${index}" destination)]] "\n"
                                 [[      if(NOT "${destination}" STREQUAL "")]] "\n"
                                 [[        file(REMOVE_RECURSE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/apps/$<TARGET_BUNDLE_DIR_NAME:]] "${cmakeSafeName}" [[>$<$<PLATFORM_ID:Darwin>:/Contents/MacOS>/${destination}")]] "\n"
                                 [[      endif()]] "\n"
                                 [[    endforeach()]] "\n"
                                 [[  endif()]] "\n"
                                 [[  cmake_policy(POP)]])
      install(CODE "${resourcesStr}")
    endif()

    if(WIN32 AND moduleKind STREQUAL "EXECUTABLE")
      install(FILES $<TARGET_PDB_FILE:${cmakeSafeName}> DESTINATION bin OPTIONAL)
    endif()
  endif()
endfunction()

endblock()
