include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(TBB_TEST OFF)
set(TBB_FIND_PACKAGE OFF)
unset(TBB_DIR CACHE)
unset(TBB_DIR)
set(TBBMALLOC_BUILD OFF)
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
      string(TOUPPER "${suffix}" suffix)
      set_property(TARGET tbb PROPERTY "${output_type}_OUTPUT_DIRECTORY_${suffix}")
    endforeach()
  endif()
endforeach()

# Remove postfixes for all configurations
if(CMAKE_CONFIGURATION_TYPES)
  foreach(suffix ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${suffix}" suffix)
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
