include(FetchContent)
message(STATUS "Fetching Vorbis...")

FetchContent_Declare(vorbis
  URL https://github.com/xiph/vorbis/releases/download/v1.3.7/libvorbis-1.3.7.tar.gz
  URL_HASH SHA256=0e982409a9c3fc82ee06e08205b1355e5c6aa4c36bca58146ef399621b0ce5ab

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

)


FetchContent_GetProperties(vorbis)
if(NOT vorbis_POPULATED)
  FetchContent_Populate(vorbis)
  # Manually define Vorbis' build and installation
  # because Vorbis does something very weird for Windows

  include(CheckLibraryExists)
  check_library_exists(m floor "" HAVE_LIBM)

  # Extract project version from configure.ac
  file(READ ${vorbis_SOURCE_DIR}/configure.ac CONFIGURE_AC_CONTENTS)
  string(REGEX MATCH "AC_INIT\\(\\[libvorbis\\],\\[([0-9]*).([0-9]*).([0-9]*)" DUMMY ${CONFIGURE_AC_CONTENTS})
  set(VORBIS_VERSION_MAJOR ${CMAKE_MATCH_1})
  set(VORBIS_VERSION_MINOR ${CMAKE_MATCH_2})
  set(VORBIS_VERSION_PATCH ${CMAKE_MATCH_3})
  set(VORBIS_VERSION ${VORBIS_VERSION_MAJOR}.${VORBIS_VERSION_MINOR}.${VORBIS_VERSION_PATCH})

  set(VORBIS_PUBLIC_HEADERS
    ${vorbis_SOURCE_DIR}/include/vorbis/codec.h
    ${vorbis_SOURCE_DIR}/include/vorbis/vorbisenc.h
    ${vorbis_SOURCE_DIR}/include/vorbis/vorbisfile.h
  )

  set(VORBIS_HEADERS
  ${vorbis_SOURCE_DIR}/lib/envelope.h
  ${vorbis_SOURCE_DIR}/lib/lpc.h
  ${vorbis_SOURCE_DIR}/lib/lsp.h
  ${vorbis_SOURCE_DIR}/lib/codebook.h
  ${vorbis_SOURCE_DIR}/lib/misc.h
  ${vorbis_SOURCE_DIR}/lib/psy.h
  ${vorbis_SOURCE_DIR}/lib/masking.h
  ${vorbis_SOURCE_DIR}/lib/os.h
  ${vorbis_SOURCE_DIR}/lib/mdct.h
  ${vorbis_SOURCE_DIR}/lib/smallft.h
  ${vorbis_SOURCE_DIR}/lib/highlevel.h
  ${vorbis_SOURCE_DIR}/lib/registry.h
  ${vorbis_SOURCE_DIR}/lib/scales.h
  ${vorbis_SOURCE_DIR}/lib/window.h
  ${vorbis_SOURCE_DIR}/lib/lookup.h
  ${vorbis_SOURCE_DIR}/lib/lookup_data.h
  ${vorbis_SOURCE_DIR}/lib/codec_internal.h
  ${vorbis_SOURCE_DIR}/lib/backends.h
  ${vorbis_SOURCE_DIR}/lib/bitrate.h
  )

  set(VORBIS_SOURCES
  ${vorbis_SOURCE_DIR}/lib/mdct.c
  ${vorbis_SOURCE_DIR}/lib/smallft.c
  ${vorbis_SOURCE_DIR}/lib/block.c
  ${vorbis_SOURCE_DIR}/lib/envelope.c
  ${vorbis_SOURCE_DIR}/lib/window.c
  ${vorbis_SOURCE_DIR}/lib/lsp.c
  ${vorbis_SOURCE_DIR}/lib/lpc.c
  ${vorbis_SOURCE_DIR}/lib/analysis.c
  ${vorbis_SOURCE_DIR}/lib/synthesis.c
  ${vorbis_SOURCE_DIR}/lib/psy.c
  ${vorbis_SOURCE_DIR}/lib/info.c
  ${vorbis_SOURCE_DIR}/lib/floor1.c
  ${vorbis_SOURCE_DIR}/lib/floor0.c
  ${vorbis_SOURCE_DIR}/lib/res0.c
  ${vorbis_SOURCE_DIR}/lib/mapping0.c
  ${vorbis_SOURCE_DIR}/lib/registry.c
  ${vorbis_SOURCE_DIR}/lib/codebook.c
  ${vorbis_SOURCE_DIR}/lib/sharedbook.c
  ${vorbis_SOURCE_DIR}/lib/lookup.c
  ${vorbis_SOURCE_DIR}/lib/bitrate.c
  )

  set(VORBISFILE_SOURCES
  ${vorbis_SOURCE_DIR}/lib/vorbisfile.c
  )

  set(VORBISENC_SOURCES
  ${vorbis_SOURCE_DIR}/lib/vorbisenc.c
  )

  if(WIN32)
      list(APPEND VORBIS_SOURCES ${vorbis_SOURCE_DIR}/lib/vorbisenc.c)
  endif()

  if(WIN32)
      list(APPEND VORBIS_SOURCES ${vorbis_SOURCE_DIR}/win32/vorbis.def)
      list(APPEND VORBISENC_SOURCES ${vorbis_SOURCE_DIR}/win32/vorbisenc.def)
      list(APPEND VORBISFILE_SOURCES ${vorbis_SOURCE_DIR}/win32/vorbisfile.def)
  endif()

  if(MSVC)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
      add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
      add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
  endif()

  if (NOT BUILD_FRAMEWORK)
      add_library(vorbis ${VORBIS_HEADERS} ${VORBIS_SOURCES})
      add_library(vorbisenc ${VORBISENC_SOURCES})
      add_library(vorbisfile ${VORBISFILE_SOURCES})

      target_include_directories(vorbis
        PUBLIC
              $<BUILD_INTERFACE:${vorbis_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>
        PRIVATE
              ${vorbis_SOURCE_DIR}
      )
      target_include_directories(vorbisenc
        PUBLIC
              $<BUILD_INTERFACE:${vorbis_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>
        PRIVATE
              ${vorbis_SOURCE_DIR}
      )
      target_include_directories(vorbisfile
          PUBLIC
            $<BUILD_INTERFACE:${vorbis_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
      )

      target_link_libraries(vorbis
          PUBLIC Ogg::ogg
          PRIVATE $<$<BOOL:${HAVE_LIBM}>:m>
      )
      target_link_libraries(vorbisenc PUBLIC vorbis)
      target_link_libraries(vorbisfile PUBLIC vorbis)

      install(TARGETS vorbis vorbisenc vorbisfile
          EXPORT VorbisTargets
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          FRAMEWORK DESTINATION lib
          PUBLIC_HEADER DESTINATION include/vorbis
      )
      set(CMAKE_INSTALL_CONFIGDIR lib/cmake/Vorbis)

      install(EXPORT VorbisTargets
          DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
          NAMESPACE Vorbis::
      )


          include(CMakePackageConfigHelpers)

          configure_package_config_file(${vorbis_SOURCE_DIR}/cmake/VorbisConfig.cmake.in ${vorbis_BINARY_DIR}/VorbisConfig.cmake
              INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
          )

          write_basic_package_version_file(${vorbis_BINARY_DIR}/VorbisConfigVersion.cmake
              COMPATIBILITY SameMajorVersion
          )

          install(FILES ${vorbis_BINARY_DIR}/VorbisConfig.cmake ${vorbis_BINARY_DIR}/VorbisConfigVersion.cmake
              DESTINATION ${CMAKE_INSTALL_CONFIGDIR}
          )
  else()
      add_library(vorbis ${VORBIS_PUBLIC_HEADERS} ${VORBIS_HEADERS} ${VORBIS_SOURCES} ${VORBISFILE_SOURCES} ${VORBISENC_SOURCES})
      set_target_properties(vorbis PROPERTIES
          FRAMEWORK TRUE
          FRAMEWORK_VERSION ${VORBIS_VERSION}
          MACOSX_FRAMEWORK_IDENTIFIER org.xiph.vorbis
          MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VORBIS_VERSION}
          MACOSX_FRAMEWORK_BUNDLE_VERSION ${VORBIS_VERSION}
          XCODE_ATTRIBUTE_INSTALL_PATH "@rpath"
          PUBLIC_HEADER "${VORBIS_PUBLIC_HEADERS}"
          OUTPUT_NAME Vorbis
      )
      target_link_libraries(vorbis ${OGG_LIBRARIES})
  endif()

endif()



#set_property(TARGET vorbis PROPERTY POSITION_INDEPENDENT_CODE ON)
#set_property(TARGET vorbisfile PROPERTY POSITION_INDEPENDENT_CODE ON)
#set_property(TARGET vorbisenc PROPERTY POSITION_INDEPENDENT_CODE ON)
set(Vorbis_Vorbis_LIBRARY "vorbis" CACHE STRING "" FORCE)
set(Vorbis_Enc_LIBRARY "vorbisenc" CACHE STRING "" FORCE)
set(Vorbis_File_LIBRARY "vorbisfile" CACHE STRING "" FORCE)
set(Vorbis_Vorbis_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" CACHE STRING "" FORCE)
set(Vorbis_Enc_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" CACHE STRING "" FORCE)
set(Vorbis_File_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src/include" CACHE STRING "" FORCE)

