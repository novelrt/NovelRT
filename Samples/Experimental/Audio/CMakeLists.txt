include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::Audio
  DEPENDS
    NovelRT::Audio

  SOURCES
    PRIVATE
      main.cpp
)
