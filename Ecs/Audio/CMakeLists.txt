include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Audio
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Audio::Core
    NovelRT::ResourceManagement::Core
    NovelRT::Logging

  SOURCES
    PRIVATE
      AudioSystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/Audio/AudioEmitterState.hpp
      include/NovelRT/Ecs/Audio/Components/AudioEmitterStateComponent.hpp
      include/NovelRT/Ecs/Audio/Components/AudioEmitterComponent.hpp
      include/NovelRT/Ecs/Audio/AudioSystem.hpp
)
