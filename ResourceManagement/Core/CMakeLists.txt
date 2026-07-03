include(NovelRTBuildSystem)


NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::ResourceManagement::Core
  DEPENDS
    NovelRT::Utilities

  SOURCES
    ResourceLoader.cpp

  HEADERS
    include/NovelRT/ResourceManagement/AudioMetadata.hpp
    include/NovelRT/ResourceManagement/BinaryDataType.hpp
    include/NovelRT/ResourceManagement/BinaryMemberMetadata.hpp
    include/NovelRT/ResourceManagement/BinaryPackage.hpp
    include/NovelRT/ResourceManagement/FontMetadata.hpp
    include/NovelRT/ResourceManagement/ResourceLoader.hpp
    include/NovelRT/ResourceManagement/ShaderMetadata.hpp
    include/NovelRT/ResourceManagement/TextureMetadata.hpp
    include/NovelRT/ResourceManagement/PlaintextAsset.hpp

  LINK_LIBRARIES
    PUBLIC
      stduuid
      nlohmann_json::nlohmann_json)
      #sndfile
      #SampleRate::samplerate)

