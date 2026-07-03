include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::Audio
  DEPENDS
    NovelRT::Audio

  SOURCES
    main.cpp
)
