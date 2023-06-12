### NovelRT - Core Library
set(NOVELRT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/NovelRT)

### Dependencies
find_package(glm REQUIRED)
find_package(TBB ${NOVELRT_ONETBB_VERSION} CONFIG REQUIRED)
find_package(Microsoft.GSL ${NOVELRT_GSL_VERSION} REQUIRED)
find_package(spdlog ${NOVELRT_SPDLOG_VERSION} REQUIRED)
find_package(nlohmann_json REQUIRED)

### Required files
set(ECS_NARRATIVE_SOURCES
  NarrativePlayerSystem.cpp
)

add_library(NovelRT_ECS_Narrative STATIC ${ECS_NARRATIVE_SOURCES})
add_dependencies(NovelRT_ECS_Narrative NovelRT_Core NovelRT_ECS runtime compiler)
set_property(TARGET NovelRT_ECS_Narrative PROPERTY VERSION ${PROJECT_VERSION})

if(GENERATOR_IS_MULTI_CONFIG)
  set_target_properties(NovelRT_ECS_Narrative PROPERTIES OUTPUT_NAME "$<IF:$<CONFIG:Release>,NovelRT_ECS_Narrative,NovelRT_ECS_Narrative-$<CONFIG>" )
else()
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ENGINE_NAME "NovelRT_ECS_Narrative")
  elseif(CMAKE_BUILD_TYPE)
    set(ENGINE_NAME "NovelRT_ECS_Narrative-${CMAKE_BUILD_TYPE}")
  else()
    set(ENGINE_NAME "NovelRT_ECS_Narrative-\$<CONFIG>")
  endif()
  set_target_properties(NovelRT_ECS_Narrative PROPERTIES OUTPUT_NAME ${ENGINE_NAME})
endif()

if(APPLE)
  get_target_property(ENGINE_NAME_FINAL NovelRT_ECS_Narrative OUTPUT_NAME)
  set_target_properties(NovelRT_ECS_Narrative PROPERTIES
    SOVERSION ${PROJECT_VERSION}
    NO_SONAME TRUE
  )
  target_link_options(NovelRT_ECS_Narrative PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-install_name @rpath/lib${ENGINE_NAME_FINAL}.dylib>)
elseif(WIN32)
  set_property(TARGET NovelRT_ECS_Narrative PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()

target_compile_features(NovelRT_ECS_Narrative PUBLIC cxx_std_17)
target_include_directories(NovelRT_ECS_Narrative
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:glm::glm,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:Microsoft.GSL::GSL,INTERFACE_INCLUDE_DIRECTORIES>>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(NovelRT_ECS_Narrative
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
  set_property(TARGET NovelRT_ECS_Narrative PROPERTY WINDOWS_EXPORT_ALL_SYMBOLS ON)
  target_compile_definitions(NovelRT_ECS_Narrative PUBLIC -D__TBB_NO_IMPLICIT_LINKAGE=$<IF:$<CONFIG:DEBUG>,1,0>)
endif()

target_link_libraries(NovelRT_ECS_Narrative
  PUBLIC
    NovelRT_Core
    NovelRT_ECS
    nlohmann_json::nlohmann_json
    runtime
)

if(NOVELRT_INSTALL)
  install(
    TARGETS NovelRT_ECS_Narrative
    EXPORT NovelRT
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    FRAMEWORK DESTINATION lib
  )
endif()

