include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)

set(BUILD_SHARED_LIBS ON)
set(INSTALL_CMAKE_PACKAGE_MODULE ON)

FetchContent_MakeAvailable(vorbis)

foreach(library vorbis vorbisenc vorbisfile)
  if(NOT TARGET "Vorbis::${library}")
    add_library("Vorbis::${library}" ALIAS "${library}")
  endif()
endforeach()

if(APPLE)
  set_target_properties(vorbis PROPERTIES NO_SONAME TRUE)
  set_target_properties(vorbisenc PROPERTIES NO_SONAME TRUE)
  set_target_properties(vorbisfile PROPERTIES NO_SONAME TRUE)
  target_link_options(vorbis PRIVATE -install_name @rpath/libvorbis.dylib)
  target_link_options(vorbisenc PRIVATE -install_name @rpath/libvorbisenc.dylib)
  target_link_options(vorbisfile PRIVATE -install_name @rpath/libvorbisfile.dylib)
endif()
