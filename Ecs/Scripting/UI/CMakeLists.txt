include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting::UI
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Ecs::Scripting::Core
    NovelRT::Ecs::UI

  SOURCES
    PRIVATE
      BranchTranslationSystem.cpp
      SpokenLineTranslationSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Scripting/UI/BranchTranslationSystem.hpp
      include/NovelRT/Ecs/Scripting/UI/SpokenLineTranslationSystem.hpp
)
