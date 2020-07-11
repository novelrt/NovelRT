include(FindPackageHandleStandardArgs)
find_package(Python REQUIRED)

execute_process(
  COMMAND ${Python_EXECUTABLE} -c "import glad; print(glad.__file__, end='')"
  OUTPUT_VARIABLE glad_LOCATION
)

if(glad_LOCATION STREQUAL "None")
  unset(glad_LOCATION)
endif()

if(glad_LOCATION)
  execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import glad; print(glad.__version__, end='')"
    OUTPUT_VARIABLE glad_VERSION
  )
endif()

find_package_handle_standard_args(glad
  REQUIRED_VARS glad_LOCATION
  VERSION_VAR glad_VERSION)

if(glad_FOUND)
  set(options NO_LOADER REPRODUCIBLE)
  set(oneValueArgs PROFILE SPEC API)

  cmake_parse_arguments(glad
    "NO_LOADER;REPRODUCIBLE"
    "PROFILE;SPEC;API"
    ""
    ${glad_FIND_COMPONENTS})

  set(glad_OUT_DIR "${CMAKE_BINARY_DIR}/glad")
  list(APPEND glad_SOURCES
    "${glad_OUT_DIR}/src/glad.c"
    "${glad_OUT_DIR}/include/glad/glad.h"
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

  add_library(glad "${glad_SOURCES}")
  target_include_directories(glad PUBLIC "${glad_OUT_DIR}/include")
  target_compile_definitions(glad
    PUBLIC
      GLAD_GLAPI_EXPORT_BUILD
  )
  add_library(Glad::GLAD ALIAS glad)
endif()
