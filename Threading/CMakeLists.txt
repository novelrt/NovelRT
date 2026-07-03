include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Threading
  DEPENDS
    NovelRT::Exceptions

  SOURCES
    VolatileState.cpp

  HEADERS
    include/NovelRT/Threading/VolatileState.hpp

  LINK_LIBRARIES
    PUBLIC
      TBB::tbb)
