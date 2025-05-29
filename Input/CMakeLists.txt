include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Input
  DEPENDS
    NovelRT::Input::Core

  OPTIONAL_DEPENDS
    NovelRT::Input::Glfw
)

add_subdirectory(Core)
add_subdirectory(Glfw)
