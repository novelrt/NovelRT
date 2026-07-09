include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Windowing::Core
  DEPENDS
    NovelRT::Graphics::Core

  SOURCES
    empty.cpp

  HEADERS
    include/NovelRT/Windowing/VideoModeData.hpp
    include/NovelRT/Windowing/WindowMode.hpp
    include/NovelRT/Windowing/WindowProvider.hpp
)
