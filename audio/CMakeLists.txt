add_library(NovelRT-Audio STATIC
  AudioMixer.cpp
  $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Win32>>:XAudio2/XAudio2AudioProvider.cpp>
  $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},macOS>>:AVAudioEngine/AVAudioEngineAudioProvider.mm>
  $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Linux>>:OpenAL/OpenALAudioProvider.cpp>
)

target_sources(NovelRT-Audio
  PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
    include/NovelRT/Audio/AudioMixer.hpp
    include/NovelRT/Audio/IAudioProvider.hpp
    include/NovelRT/Audio/AudioSourceContext.hpp
    include/NovelRT/Audio/AudioSourceState.hpp
)

target_sources(NovelRT-Audio
  PRIVATE
    FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
    $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Win32>>:include/NovelRT/Audio/XAudio2/XAudio2AudioProvider.hpp>
    $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Linux>>:include/NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp>
    $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},macOS>>:include/NovelRT/Audio/AVAudioEngine/AVAudioEngineAudioProvider.hpp>
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
    $<$<BOOL:$<STREQUAL:${NOVELRT_TARGET},Linux>>:OpenAL>
)

if(${NOVELRT_TARGET} STREQUAL "macOS")
  target_link_libraries(NovelRT-Audio
    PRIVATE
      "-framework AVFoundation"
  )
endif()

install(
  TARGETS NovelRT-Audio
  EXPORT NovelRTConfig
  LIBRARY DESTINATION lib
  FILE_SET public_headers DESTINATION include
)
