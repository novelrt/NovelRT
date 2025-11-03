include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Graphics
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Graphics

  SOURCES
    PRIVATE
      RenderOrchestratorSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Graphics/GraphicsComponents.hpp
      include/NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp
)
