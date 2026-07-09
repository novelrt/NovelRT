
include(NovelRTBuildSystem)


NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::ResourceManagement::Desktop
    DEPENDS
      NovelRT::ResourceManagement::Core
      NovelRT::Utilities
      NovelRT::Logging

  SOURCES
    DesktopResourceLoader.cpp
    DesktopResourceManagementPluginProvider.cpp

  HEADERS
    include/NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp
    include/NovelRT/ResourceManagement/Desktop/DesktopResourceManagementPluginProvider.hpp
    include/NovelRT/ResourceManagement/Desktop/ImageData.hpp
      
  LINK_LIBRARIES
    PUBLIC
      PNG::png
      sndfile
      SampleRate::samplerate)
