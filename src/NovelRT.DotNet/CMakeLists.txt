include(CopyDependencyOutputs)

if(NOVELRT_GENERATOR_IS_MULTI_CONFIG)
  set(NOVELRT_DOTNET_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")
else()
  set(NOVELRT_DOTNET_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
endif()
mark_as_advanced(NOVELRT_DOTNET_OUTPUT_DIR)

set(NOVELRT_DOTNET_CSPROJ
  ${CMAKE_CURRENT_SOURCE_DIR}/NovelRT.DotNet.csproj)
set(NOVELRT_DOTNET_VALID_CONFIGURATIONS
  Debug Release)

list(FIND NOVELRT_DOTNET_VALID_CONFIGURATIONS "${CMAKE_BUILD_TYPE}" _NovelRT_DotNet_BuildType)
mark_as_advanced(_NovelRT_DotNet_BuildType)

if (${_NovelRT_DotNet_BuildType} GREATER 0)
  set(NOVELRT_DOTNET_CONFIGURATION ${CMAKE_BUILD_TYPE})
else()
  set(NOVELRT_DOTNET_CONFIGURATION Release)
endif()

execute_process(
  COMMAND dotnet msbuild "${NOVELRT_DOTNET_CSPROJ}" /noLogo /target:CMakeGetInputFiles /p:Configuration=${NOVELRT_DOTNET_CONFIGURATION} "/p:OutDir=${NOVELRT_DOTNET_OUTPUT_DIR}"
  OUTPUT_VARIABLE _NovelRT_DotNet_InputFiles)
string(STRIP "${_NovelRT_DotNet_InputFiles}" _NovelRT_DotNet_InputFiles)

list(TRANSFORM _NovelRT_DotNet_InputFiles PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM _NovelRT_DotNet_InputFiles REPLACE "[\\]" "/")

execute_process(
  COMMAND dotnet msbuild "${NOVELRT_DOTNET_CSPROJ}" /noLogo /target:CMakeGetOutputFiles /p:Configuration=${NOVELRT_DOTNET_CONFIGURATION} "/p:OutDir=${NOVELRT_DOTNET_OUTPUT_DIR}"
  OUTPUT_VARIABLE _NovelRT_DotNet_OutputFiles)
string(STRIP "${_NovelRT_DotNet_OutputFiles}" _NovelRT_DotNet_OutputFiles)

list(APPEND _NovelRT_DotNet_OutputFiles NovelRT.DotNet.runtimeconfig.json)
list(TRANSFORM _NovelRT_DotNet_OutputFiles PREPEND "${NOVELRT_DOTNET_OUTPUT_DIR}/")
list(TRANSFORM _NovelRT_DotNet_OutputFiles REPLACE "[\\]" "/")

mark_as_advanced(_NovelRT_DotNet_InputFiles _NovelRT_DotNet_OutputFiles)

add_custom_command(
  OUTPUT ${_NovelRT_DotNet_OutputFiles}
  COMMAND dotnet build "${NOVELRT_DOTNET_CSPROJ}" --nologo /p:Configuration=${NOVELRT_DOTNET_CONFIGURATION} "/p:OutDir=${NOVELRT_DOTNET_OUTPUT_DIR}"
  MAIN_DEPENDENCY ${NOVELRT_DOTNET_CSPROJ}
  DEPENDS ${_NovelRT_DotNet_InputFiles}
  COMMENT "Building .NET Project NovelRT.DotNet")


add_custom_target(NovelRT_DotNet ALL
  DEPENDS "${_NovelRT_DotNet_OutputFiles}"
  SOURCES "${_NovelRT_DotNet_InputFiles}")

add_dependency_outputs(NovelRT_DotNet ${_NovelRT_DotNet_OutputFiles})
