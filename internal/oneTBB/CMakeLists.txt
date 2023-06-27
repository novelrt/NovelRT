include(FetchContent)
message(STATUS "Fetching oneTBB")
set(TBB_TEST OFF CACHE BOOL "Build TBB Tests" FORCE)
set(TBBMALLOC_BUILD OFF CACHE BOOL "Build tbbmalloc" FORCE)

FetchContent_Declare(TBB
        URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip
        URL_HASH SHA512=fde7eb56b46fa86b619eb60e587728d19f31639ec06dfd5d7af0dab00ffba38606d7a89dcf050c4cdfa8896560a7424a3431619108f395348dadf60ad6b67a1b

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

set(BUILD_SHARED_LIBS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
FetchContent_MakeAvailable(TBB)

# Unset the output directories for TBB so that they are generated in the correct location.
foreach(output_type LIBRARY ARCHIVE PDB RUNTIME)
  if(CMAKE_BUILD_TYPE)
    set_property(TARGET tbb PROPERTY "${output_type}_OUTPUT_DIRECTORY")
  endif()

  if(CMAKE_CONFIGURATION_TYPES)
    foreach(suffix ${CMAKE_CONFIGURATION_TYPES})
      string(UPPER "${suffix}" suffix)
      set_property(TARGET tbb PROPERTY "${output_type}_OUTPUT_DIRECTORY_${suffix}")
    endforeach()
  endif()
endforeach()

# Remove postfixes for all configurations
if(CMAKE_CONFIGURATION_TYPES)
  foreach(suffix ${CMAKE_CONFIGURATION_TYPES})
    string(UPPER "${suffix}" suffix)
    set_property(TARGET tbb PROPERTY "${suffix}_POSTFIX")
  endforeach()
endif()

set_property(TARGET tbb PROPERTY DEBUG_POSTFIX)

# Instead set the output name based on the config
get_target_property(prefix tbb OUTPUT_NAME)
if(prefix)
  set_target_properties(tbb
    PROPERTIES
      OUTPUT_NAME "${prefix}-$<CONFIG>")
else()
  set_target_properties(tbb
    PROPERTIES
      OUTPUT_NAME "tbb-$<CONFIG>")
endif()

# Hack: TBB tries to hardcode paths to search for libraries and this breaks the build.
if(WIN32)
  target_compile_definitions(tbb
    PUBLIC
      -D__TBB_NO_IMPLICIT_LINKAGE=1)
endif()

if(APPLE)
  set_target_properties(tbb PROPERTIES NO_SONAME TRUE)
  target_link_options(tbb PRIVATE -install_name @rpath/libtbb.dylib)
endif()
