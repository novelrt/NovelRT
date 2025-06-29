include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Graphics
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Graphics

  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Graphics/GraphicsComponents.hpp
)
