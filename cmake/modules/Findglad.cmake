include(FindPackageHandleStandardArgs)
find_package(Python REQUIRED)

execute_process(
  COMMAND ${Python_EXECUTABLE} -c "import glad; print(glad.__file__, end='')"
  OUTPUT_VARIABLE glad_LOCATION
)

execute_process(
  COMMAND ${Python_EXECUTABLE} -c "import glad; print(glad.__version__, end='')"
  OUTPUT_VARIABLE glad_VERSION
)

set(options NO_LOADER REPRODUCIBLE)
set(oneValueArgs PROFILE SPEC API)

cmake_parse_arguments(glad "${options}" "${oneValueArgs}" "${multiValueArgs}"
  ${glad_FIND_COMPONENTS})

set(glad_OUT_DIR "${CMAKE_BINARY_DIR}/glad")
set(glad_INCLUDE_DIRS "${glad_OUT_DIR}/include")
list(APPEND glad_SOURCES
  "${glad_OUT_DIR}/src/glad.c"
  "${glad_INCLUDE_DIRS}/glad/glad.h"
)

file(MAKE_DIRECTORY "${glad_OUT_DIR}/include")

add_custom_command(
  OUTPUT ${glad_SOURCES}
  COMMAND ${Python_EXECUTABLE} -m glad
    --quiet
    --profile=${glad_PROFILE}
    --out-path=${glad_OUT_DIR}
    --api=${glad_API}
    --spec=${glad_SPEC}
    $<$<BOOL:${glad_NO_LOADER}>:--no-loader>
    $<$<BOOL:${glad_REPRODUCIBLE}>:--reproducible>
    $<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,--generator=c-debug,--generator=c>
  COMMENT "Generating GLAD"
)

set_source_files_properties(${glad_SOURCES} PROPERTIES GENERATED TRUE)

add_library(glad STATIC IMPORTED)

set_target_properties(glad PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${glad_INCLUDE_DIRS}"
  INTERFACE_SOURCES "${glad_SOURCES}")

find_package_handle_standard_args(glad
  REQUIRED_VARS glad_LOCATION
  VERSION_VAR glad_VERSION)
