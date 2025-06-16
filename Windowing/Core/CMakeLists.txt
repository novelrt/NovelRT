include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Windowing::Core
  DEPENDS
    NovelRT::Graphics::Core

  HEADERS
    PUBLIC
      include/NovelRT/Windowing/WindowMode.hpp
      include/NovelRT/Windowing/WindowProvider.hpp
)
