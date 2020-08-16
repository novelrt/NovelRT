set(INTEROP_SOURCES
  #NovelRunner_t.cpp
  NovelRTTransform.cpp
  NovelRTInteropUtils.cpp
  #Maths/GeoMatrix4x4F_t.cpp
  Maths/NovelRTGeoBounds.cpp
  Maths/NovelRTGeoVector2F.cpp
  Maths/NovelRTGeoVector3F.cpp
  #Maths/GeoVector4F_t.cpp
  #Maths/QuadTree_t.cpp
  #Maths/QuadTreePoint_t.cpp
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
  )
endif()

target_link_libraries(Interop
  PUBLIC
    Engine)