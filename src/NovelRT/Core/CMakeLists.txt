### NovelRT - Core Library
set(NOVELRT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/NovelRT)

set(CORE_HEADERS
  ${NOVELRT_INCLUDE_DIR}/Core/Core.h
  ${NOVELRT_INCLUDE_DIR}/Core/Atom.h
  ${NOVELRT_INCLUDE_DIR}/Core/EngineConfig.h
  ${NOVELRT_INCLUDE_DIR}/Core/LoggingService.h

  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/Exceptions.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/CharacterNotFoundException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/CompilationErrorException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/DuplicateKeyException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/FileNotFoundException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/FunctionNotFoundException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/InitialisationFailureException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/InvalidOperationException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/IOException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/KeyNotFoundException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/NotInitialisedException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/NotSupportedException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/NullPointerException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/OpenGLLinkageFailureException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/OutOfMemoryException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/RuntimeNotFoundException.h
  ${NOVELRT_INCLUDE_DIR}/Core/Exceptions/TimeoutException.h

  ${NOVELRT_INCLUDE_DIR}/Core/Utilities/Utilities.h
  ${NOVELRT_INCLUDE_DIR}/Core/Utilities/Event.h
  ${NOVELRT_INCLUDE_DIR}/Core/Utilities/KeyValuePair.h
  ${NOVELRT_INCLUDE_DIR}/Core/Utilities/Lazy.h
  ${NOVELRT_INCLUDE_DIR}/Core/Utilities/Misc.h
)

set(CORE_SOURCES
  Atom.cpp
  LoggingService.cpp
  EngineConfig.cpp
  Utilities/Misc.cpp
)

add_library(NovelRT_Core STATIC ${CORE_SOURCES})
set_property(TARGET NovelRT_Core PROPERTY VERSION ${PROJECT_VERSION})

if(GENERATOR_IS_MULTI_CONFIG)
  set_target_properties(NovelRT_Core PROPERTIES OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT_Core,NovelRT_Core-$<CONFIG>" )
else()
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ENGINE_NAME "NovelRT_Core")
  elseif(CMAKE_BUILD_TYPE)
    set(ENGINE_NAME "NovelRT_Core-${CMAKE_BUILD_TYPE}")
  else()
    set(ENGINE_NAME "NovelRT_Core-\$<CONFIG>")
  endif()
  set_target_properties(NovelRT_Core PROPERTIES OUTPUT_NAME ${ENGINE_NAME})
endif()

if(APPLE)
  get_target_property(ENGINE_NAME_FINAL NovelRT_Core OUTPUT_NAME)
  set_target_properties(NovelRT_Core PROPERTIES
    SOVERSION ${PROJECT_VERSION}
    NO_SONAME TRUE
  )
  target_link_options(NovelRT_Core PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-install_name @rpath/lib${ENGINE_NAME_FINAL}.dylib>)
elseif(WIN32)
  set_property(TARGET NovelRT_Core PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

target_compile_features(NovelRT_Core PUBLIC cxx_std_17)
target_include_directories(NovelRT_Core
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:glm::glm,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:Microsoft.GSL::GSL,INTERFACE_INCLUDE_DIRECTORIES>>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(NovelRT_Core
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<CXX_COMPILER_ID:MSVC>:/wd4611>
    $<$<CXX_COMPILER_ID:MSVC>:/MP>

    $<$<CXX_COMPILER_ID:GNU>:-pedantic>
    $<$<CXX_COMPILER_ID:GNU>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-padded>

    $<$<CXX_COMPILER_ID:Clang>:-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:Clang>:-Wall>
    $<$<CXX_COMPILER_ID:Clang>:-Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Werror>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-reserved-id-macro>

    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-pedantic-errors>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wextra>
    $<$<CXX_COMPILER_ID:AppleClang>:-Werror>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-c++98-compat-pedantic>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-float-equal>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-padded>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wno-reserved-id-macro>
)

if(MSVC)
  set_property(TARGET NovelRT_Core PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_compile_definitions(NovelRT_Core PUBLIC -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0>)
endif()

target_link_libraries(NovelRT_Core
  PUBLIC
    TBB::tbb
    spdlog::spdlog
)

if(NOVELRT_INSTALL)
  install(
    TARGETS NovelRT_Core
    EXPORT NovelRT
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    FRAMEWORK DESTINATION lib
  )
endif()

