include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Base
  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Utilities/BitCast.hpp
      include/NovelRT/Utilities/Lazy.hpp
      include/NovelRT/Utilities/Operators.hpp
      include/NovelRT/Utilities/Span.hpp

  LINK_LIBRARIES
    PUBLIC
      Microsoft.GSL::GSL
      glm::glm)
