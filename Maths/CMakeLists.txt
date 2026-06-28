include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Maths
  DEPENDS
    NovelRT::Utilities
    NovelRT::Exceptions

  SOURCES
    PRIVATE
      GeoBounds.cpp
      QuadTree.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Maths/Constants.hpp
      include/NovelRT/Maths/GeoBounds.hpp
      include/NovelRT/Maths/GeoMatrix4x4F.hpp
      include/NovelRT/Maths/GeoVector2F.hpp
      include/NovelRT/Maths/GeoVector3F.hpp
      include/NovelRT/Maths/GeoVector4F.hpp
      include/NovelRT/Maths/Utilities.hpp

  COMPILE_DEFINITIONS
    PUBLIC
      GLM_ENABLE_EXPERIMENTAL=1
      GLM_FORCE_DEPTH_ZERO_TO_ONE

  LINK_LIBRARIES
    PUBLIC
      glm::glm-header-only)
