include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Graphics
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Graphics
    NovelRT::ResourceManagement::Desktop

  SOURCES
    PRIVATE
      RenderOrchestratorSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp
      include/NovelRT/Ecs/Graphics/Components/RenderPass.hpp
      include/NovelRT/Ecs/Graphics/Components/Sprite.hpp
      include/NovelRT/Ecs/Graphics/EcsGraphicsBuilder.hpp
      include/NovelRT/Ecs/Graphics/RenderOrchestratorSystem.hpp
      include/NovelRT/Ecs/Graphics/SpriteRendererSystem.hpp
      include/NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp
)
