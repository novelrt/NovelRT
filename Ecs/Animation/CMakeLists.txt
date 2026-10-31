include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Animation
  DEPENDS
    NovelRT::Ecs::Core

  SOURCES
    empty.cpp

  HEADERS
    include/NovelRT/Ecs/Animation/Easing.hpp
    include/NovelRT/Ecs/Animation/Tween.hpp
)
