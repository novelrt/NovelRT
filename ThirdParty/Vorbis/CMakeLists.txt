include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)

set(BUILD_SHARED_LIBS ON)
set(INSTALL_CMAKE_PACKAGE_MODULE ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_MakeAvailable(vorbis)

foreach(library vorbis vorbisenc vorbisfile)
  if(NOT TARGET "Vorbis::${library}")
    add_library("Vorbis::${library}" ALIAS "${library}")
  endif()
endforeach()
