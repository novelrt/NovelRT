add_library(NovelRT-Audio STATIC
  #AudioService.cpp
  AudioEngine.cpp
)

target_sources(NovelRT-Audio
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
      include/NovelRT/Audio/Audio.hpp
)

set_target_properties(NovelRT-Audio
  PROPERTIES
    EXPORT_NAME Audio
    POSITION_INDEPENDENT_CODE ON
)

target_compile_features(NovelRT-Audio
  PUBLIC
    cxx_std_17
)

target_compile_options(NovelRT-Audio
  PRIVATE
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
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

target_include_directories(NovelRT-Audio PRIVATE "$<TARGET_PROPERTY:Engine,INCLUDE_DIRECTORIES>")
target_link_libraries(NovelRT-Audio
  PUBLIC
    spdlog
    OpenAL
)

install(
  TARGETS NovelRT-Audio
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
