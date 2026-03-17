include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::ResourceManagement
  DEPENDS
    NovelRT::ResourceManagement::Core)

  #LINK_LIBRARIES
  #  PUBLIC
  #    stduuid
  #    PNG::png
  #    nlohmann_json::nlohmann_json
  #    sndfile
  #    SampleRate::samplerate)

  add_subdirectory(Core)
  add_subdirectory(Desktop)
