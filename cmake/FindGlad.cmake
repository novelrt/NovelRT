# Finds the glad library

# This file can be configured with the following CMake variables:
# - GLAD_ROOT_DIR
# - GLAD_INCLUDE_DIR
# - GLAD_LIBRARY

# Or, alternatively, the following environment variables:
# - GLAD_INSTALL_DIR
# - LIBRARY_PATH

include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

pkg_check_modules(PC_GLAD QUIET glad)

set(GLAD_DEFINITIONS ${PC_GLAD_CFLAGS_OTHER})
set(GLAD_SEARCH_DIR ${GLAD_ROOT_DIR} $ENV{GLAD_INSTALL_DIR})

find_path(GLAD_INCLUDE_DIR
  glad/glad.h
  HINTS ${GLAD_SEARCH_DIR} ${PC_GLAD_INCLUDEDIR} ${PC_GLAD_INCLUDE_DIRS}
  PATH_SUFFIXES include
)

find_library(GLAD_LIBRARY
  NAMES glad
  HINTS ${GLAD_SEARCH_DIR} ${PC_GLAD_LIBDIR} ${PC_GLAD_LIBRARY_DIRS}
  PATH_SUFFIXES lib bin
  ENV LIBRARY_PATH
)

set(GLAD_LIBRARIES ${GLAD_LIBRARY})
set(GLAD_INCLUDE_DIRS ${GLAD_INCLUDE_DIR})
set(GLAD_VERSION ${PC_GLAD_VERSION})

find_package_handle_standard_args(Glad
  REQUIRED_VARS GLAD_LIBRARIES GLAD_INCLUDE_DIR
  VERSION_VAR GLAD_VERSION
  HANDLE_COMPONENTS
)

if(GLAD_FOUND)
  add_library(Glad::Glad UNKNOWN IMPORTED)
  set_target_properties(Glad::Glad PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${GLAD_INCLUDE_DIRS}"
    IMPORTED_LOCATION "${GLAD_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${GLAD_DEFINITIONS}"
  )
else()
  find_package(Python)

  if(PYTHON_FOUND)
    execute_process(
      COMMAND ${PYTHON_EXECUTABLE} -c "import glad; print(glad.__file__, end='')"
      OUTPUT_VARIABLE GLAD_LOCATION
    )

    if(GLAD_LOCATION STREQUAL "None")
      unset(GLAD_LOCATION)
    endif()

    if(GLAD_LOCATION)
      execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import glad; print(glad.__version__, end='')"
        OUTPUT_VARIABLE GLAD_VERSION
      )
    endif()

    find_package_handle_standard_args(glad
      REQUIRED_VARS GLAD_LOCATION
      VERSION_VAR GLAD_VERSION
    )

    if(GLAD_FOUND)
      set(options NO_LOADER REPRODUCIBLE)
      set(oneValueArgs PROFILE SPEC API)

      cmake_parse_arguments(GLAD
        "NO_LOADER;REPRODUCIBLE"
        "PROFILE;SPEC;API"
        ""
        ${GLAD_FIND_COMPONENTS}
      )

      set(GLAD_OUT_DIR "${CMAKE_BINARY_DIR}/glad")
      list(APPEND GLAD_SOURCES
        "${GLAD_OUT_DIR}/src/glad.c"
        "${GLAD_OUT_DIR}/include/glad/glad.h"
      )

      file(MAKE_DIRECTORY "${GLAD_OUT_DIR}/include")

      add_custom_command(
        OUTPUT ${GLAD_SOURCES}
        COMMAND ${PYTHON_EXECUTABLE} -m glad
          --quiet
          --profile=${GLAD_PROFILE}
          --out-path=${GLAD_OUT_DIR}
          --api=${GLAD_API}
          --spec=${GLAD_SPEC}
          $<$<BOOL:${GLAD_NO_LOADER}>:--no-loader>
          $<$<BOOL:${GLAD_REPRODUCIBLE}>:--reproducible>
          $<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,--generator=c-debug,--generator=c>
        COMMENT "Generating GLAD"
      )

      add_library(Glad::Glad STATIC "${GLAD_SOURCES}")
      set_target_properties(Glad::Glad PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
      target_include_directories(Glad::Glad PUBLIC "${GLAD_OUT_DIR}/include")
      target_compile_definitions(Glad::Glad
        PUBLIC
          GLAD_GLAPI_EXPORT_BUILD
      )
    endif()
  endif()
endif()

mark_as_advanced(GLAD_INCLUDE_DIRS GLAD_LIBRARIES)
