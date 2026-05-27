include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Scripting
  DEPENDS
    NovelRT::Scripting::Core
)

add_subdirectory(Core)
