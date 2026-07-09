include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::Audio
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Audio::Core
    NovelRT::ResourceManagement::Core
    NovelRT::Logging

  SOURCES
    AudioSystem.cpp

  HEADERS
    include/NovelRT/Ecs/Audio/AudioEmitterState.hpp
    include/NovelRT/Ecs/Audio/Components/AudioEmitterStateComponent.hpp
    include/NovelRT/Ecs/Audio/Components/AudioEmitterComponent.hpp
    include/NovelRT/Ecs/Audio/AudioSystem.hpp
    include/NovelRT/Ecs/Audio/EcsAudioBuilder.hpp
)
