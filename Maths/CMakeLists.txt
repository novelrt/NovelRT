include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Maths
  DEPENDS
    NovelRT::Utilities

  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Maths/Constants.hpp
      include/NovelRT/Maths/GeoVector2F.hpp
      include/NovelRT/Maths/GeoVector3F.hpp
      include/NovelRT/Maths/GeoVector4F.hpp
      include/NovelRT/Maths/Utilities.hpp

  COMPILE_DEFINITIONS
    PUBLIC
      GLM_ENABLE_EXPERIMENTAL=1

  LINK_LIBRARIES
    PUBLIC
      glm::glm-header-only)
