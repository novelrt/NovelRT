include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Scripting::Core
  DEPENDS
    NovelRT::Exceptions
    lua::lua

  SOURCES
    PRIVATE
      empty.cpp
)
