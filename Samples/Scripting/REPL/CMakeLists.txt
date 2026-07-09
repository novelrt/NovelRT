include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Scripting::REPL
  DEPENDS
    NovelRT::ResourceManagement::Desktop
    NovelRT::Scripting

  SOURCES
    main.cpp

  RESOURCES
    Resources/sample.lua
)
