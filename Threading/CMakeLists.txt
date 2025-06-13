include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Threading
  DEPENDS
    NovelRT::Exceptions

  SOURCES
    PRIVATE
      VolatileState.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Threading/VolatileState.hpp

  LINK_LIBRARIES
    PUBLIC
      TBB::tbb)
