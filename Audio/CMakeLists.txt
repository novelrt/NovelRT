include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Audio
  DEPENDS
    NovelRT::Audio::Core

  OPTIONAL_DEPENDS
    NovelRT::Audio::OpenAL)

add_subdirectory(Core)

add_subdirectory(OpenAL)

# TODO: XAudio, AVAudioEngine
