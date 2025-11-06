include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Maths
  DEPENDS
    NovelRT::Utilities

  SOURCES
    PUBLIC
      Public/Constants.cpp
      Public/GeoVector2F.cpp
      Public/GeoVector3F.cpp
      Public/GeoVector4F.cpp
      Public/Utilities.cpp

  COMPILE_DEFINITIONS
    PRIVATE
      GLM_ENABLE_EXPERIMENTAL=1

  LINK_LIBRARIES
    PRIVATE
      glm::glm-header-only)
