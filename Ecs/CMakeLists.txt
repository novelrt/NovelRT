include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs
  DEPENDS
    NovelRT::Ecs::Core

  OPTIONAL_DEPENDS
    NovelRT::Ecs::Animation
    NovelRT::Ecs::Audio
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::Scripting
    NovelRT::Ecs::UI
)

# Ordered this to reflect the DeclareModule declaration above. OPTIONAL_DEPENDS is ordered based on the folder order.
add_subdirectory(Core)
add_subdirectory(Animation)
add_subdirectory(Audio)
add_subdirectory(Graphics)
add_subdirectory(Scripting)
add_subdirectory(UI)
