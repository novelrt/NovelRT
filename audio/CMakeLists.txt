add_library(NovelRT-Audio STATIC
  AudioMixer.cpp
  $<$<BOOL:${WIN32}>:XAudio2/XAudio2AudioProvider.cpp>
  $<$<BOOL:${UNIX}>:OpenAL/OpenALAudioProvider.cpp>
  $<$<BOOL:${APPLE}>:OpenAL/OpenALAudioProvider.cpp>
)

target_sources(NovelRT-Audio
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
    include/NovelRT/Audio/AudioMixer.hpp
    include/NovelRT/Audio/IAudioProvider.hpp
    $<$<BOOL:${WIN32}>:include/NovelRT/Audio/XAudio2/XAudio2AudioProvider.hpp>
    $<$<BOOL:${UNIX}>:include/NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
    $<$<BOOL:${APPLE}>:include/NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
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
    $<$<BOOL:${APPLE}>:OpenAL>
    $<$<BOOL:${UNIX}>:OpenAL>
)

install(
  TARGETS NovelRT-Audio
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
