include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Windowing
  DEPENDS
    NovelRT::Windowing::Core

  OPTIONAL_DEPENDS
    NovelRT::Windowing::Glfw
)

add_subdirectory(Core)
add_subdirectory(Glfw)
