set(INTEROP_SOURCES
  NovelRTNovelRunner.cpp
  NovelRTTransform.cpp
  NovelRTInteropUtils.cpp

  Audio/NovelRTAudioService.cpp

  Input/NovelRTBasicInteractionRect.cpp
  Input/NovelRTInteractionService.cpp
  Input/NovelRTKeyStateFrameChangeLog.cpp
  
  Maths/NovelRTGeoMatrix4x4F.cpp
  Maths/NovelRTGeoBounds.cpp
  Maths/NovelRTGeoVector2F.cpp
  Maths/NovelRTGeoVector3F.cpp
  Maths/NovelRTGeoVector4F.cpp
  Maths/NovelRTQuadTree.cpp
  Maths/NovelRTQuadTreePoint.cpp

  Windowing/NovelRTWindowingService.cpp
)

add_library(Interop SHARED ${INTEROP_SOURCES})
add_dependencies(Interop Engine)

target_include_directories(Interop
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


if(MSVC)
  target_compile_options(Interop
    PRIVATE
      /W4
      /WX
      /wd4611
      /wd4100
  )
  get_target_property(opts Interop COMPILE_OPTIONS)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(Interop
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-float-equal
      -Wno-padded
      -Wno-unused-parameter
  )
else()
  target_compile_options(Interop
    PRIVATE
      -pedantic
      -pedantic-errors
      -Wall
      -Wextra
      -Werror
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-float-equal
      -Wno-padded
      -Wno-reserved-id-macro
      -Wno-unused-parameter
  )
endif()

target_link_libraries(Interop
  PUBLIC
    Engine)