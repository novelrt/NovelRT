include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Scripting::REPL
  DEPENDS
    NovelRT::ResourceManagement::Desktop
    NovelRT::Scripting

  SOURCES
    PRIVATE
      main.cpp

  RESOURCES
    PUBLIC
      Resources/sample.lua
)
