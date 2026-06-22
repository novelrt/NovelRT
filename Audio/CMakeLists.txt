include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Audio
  DEPENDS
    NovelRT::Audio::Core

  OPTIONAL_DEPENDS
    NovelRT::Audio::OpenAL)

add_subdirectory(Core)

find_package(OpenAL "1.23.1" OPTIONAL)
if(OpenAL_FOUND)
  add_subdirectory(OpenAL)
endif()

# TODO: XAudio, AVAudioEngine
