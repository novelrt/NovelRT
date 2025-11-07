include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::ResourceManagement
  DEPENDS
    NovelRT::Utilities
    NovelRT::Logging

  SOURCES
    PRIVATE
      Desktop/DesktopResourceLoader.cpp
      Desktop/DesktopResourceManagementPluginProvider.cpp
      ResourceLoader.cpp

  HEADERS
    PUBLIC
      include/NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp
      include/NovelRT/ResourceManagement/Desktop/DesktopResourceManagementPluginProvider.hpp
      include/NovelRT/ResourceManagement/Desktop/ImageData.hpp
      include/NovelRT/ResourceManagement/AudioMetadata.hpp
      include/NovelRT/ResourceManagement/BinaryDataType.hpp
      include/NovelRT/ResourceManagement/BinaryMemberMetadata.hpp
      include/NovelRT/ResourceManagement/BinaryPackage.hpp
      include/NovelRT/ResourceManagement/ResourceLoader.hpp
      include/NovelRT/ResourceManagement/ShaderMetadata.hpp
      include/NovelRT/ResourceManagement/TextureMetadata.hpp

  LINK_LIBRARIES
    PUBLIC
      stduuid
      PNG::png
      nlohmann_json::nlohmann_json
      sndfile
      SampleRate::samplerate)
