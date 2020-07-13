# Finds the .NET Core CLI

# This file can be configured with the following CMake variables:
# - Dotnet_ROOT_DIR

# Or, alternatively, the following environment variables:
# - Dotnet_INSTALL_DIR

include(FindPackageHandleStandardArgs)

find_program(
  Dotnet_PROGRAM
  NAMES dotnet
  HINTS ${Dotnet_ROOT_DIR}
  ENV ${Dotnet_INSTALL_DIR}
)

if(Dotnet_PROGRAM)
  execute_process(
    COMMAND ${Dotnet_PROGRAM} --version
    OUTPUT_VARIABLE Dotnet_VERSION
  )
  string(STRIP "${Dotnet_VERSION}" Dotnet_VERSION)
endif()

find_package_handle_standard_args(Dotnet
  REQUIRED_VARS Dotnet_PROGRAM
  VERSION_VAR Dotnet_VERSION
)

if(Dotnet_FOUND)
  add_executable(Dotnet::CLI IMPORTED)
  set_target_properties(Dotnet::CLI
    PROPERTIES
      IMPORTED_LOCATION ${Dotnet_PROGRAM}
  )
endif()

mark_as_advanced(Dotnet_PROGRAM)
