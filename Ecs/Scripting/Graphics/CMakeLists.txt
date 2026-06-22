include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting::Graphics
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Ecs::Scripting::Core
    NovelRT::Ecs::Graphics
    NovelRT::ResourceManagement

  SOURCES
    PRIVATE
      PoseToSpriteTranslationSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Scripting/Graphics/PoseToSpriteTranslationSystem.hpp
)
