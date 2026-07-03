include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Scripting::UI
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Ecs::Scripting::Core
    NovelRT::Ecs::UI

  SOURCES
    BranchTranslationSystem.cpp
    SpokenLineTranslationSystem.cpp

  HEADERS
    include/NovelRT/Ecs/Scripting/UI/BranchTranslationSystem.hpp
    include/NovelRT/Ecs/Scripting/UI/SpokenLineTranslationSystem.hpp
)
