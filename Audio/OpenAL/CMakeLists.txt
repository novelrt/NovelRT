include(NovelRTBuildSystem)

find_package(OpenAL "1.23.1" REQUIRED)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Audio::OpenAL
  DEPENDS
    NovelRT::Logging
    NovelRT::Audio::Core

  SOURCES
    PRIVATE
      OpenALAudioProvider.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Audio/OpenAL/OpenALAudioProvider.hpp

  LINK_LIBRARIES
    PUBLIC
      OpenAL::OpenAL)
