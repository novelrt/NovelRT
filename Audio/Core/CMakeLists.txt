include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Audio::Core
  DEPENDS
    NovelRT::Utilities

  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Audio/AudioMixer.hpp
      include/NovelRT/Audio/AudioProvider.hpp
      include/NovelRT/Audio/AudioSourceContext.hpp
      include/NovelRT/Audio/AudioSourceState.hpp)
