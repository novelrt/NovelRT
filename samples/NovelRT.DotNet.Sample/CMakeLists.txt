find_package(Dotnet ${NOVELRT_DOTNET_VERSION} REQUIRED)

set(DOTNET_SAMPLE_CSPROJ ${CMAKE_CURRENT_LIST_DIR}/NovelRT.DotNet.Sample.csproj)

set(DOTNET_SAMPLE_SOURCES
  NovelRT.DotNet.Sample.runtimeconfig.json
  Program.cs
)

set(DOTNET_SAMPLE_OPTIONS
  /nologo
  /p:IntermediateOutputPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Sample_Build.dir/
  /p:MSBuildProjectExtensionsPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Sample_Build.dir/
  /p:OutDir=${CMAKE_CURRENT_BINARY_DIR}/
  /p:PublishDir=${CMAKE_CURRENT_BINARY_DIR}/publish/
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${DOTNET_SAMPLE_CSPROJ} ${DOTNET_SAMPLE_OPTIONS}
  /t:Restore
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${DOTNET_SAMPLE_CSPROJ} ${DOTNET_SAMPLE_OPTIONS}
  /t:GetCMakeOutputAssembly
  OUTPUT_VARIABLE DOTNET_SAMPLE_OUTPUT_ASSEMBLY
)
string(STRIP "${DOTNET_SAMPLE_OUTPUT_ASSEMBLY}" DOTNET_SAMPLE_OUTPUT_ASSEMBLY)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${DOTNET_SAMPLE_CSPROJ} ${DOTNET_SAMPLE_OPTIONS}
  /t:GetCMakeOutputByproducts
  OUTPUT_VARIABLE DOTNET_SAMPLE_OUTPUT_BYPRODUCTS
)
string(STRIP "${DOTNET_SAMPLE_OUTPUT_BYPRODUCTS}" DOTNET_SAMPLE_OUTPUT_BYPRODUCTS)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/publish)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${DOTNET_SAMPLE_OUTPUT_ASSEMBLY}
  DEPENDS ${DOTNET_SAMPLE_SOURCES} ${DOTNET_SAMPLE_CSPROJ}
  BYPRODUCTS ${DOTNET_SAMPLE_OUTPUT_BYPRODUCTS}
  COMMAND ${Dotnet_PROGRAM} msbuild ${DOTNET_SAMPLE_CSPROJ} ${DOTNET_SAMPLE_OPTIONS}
  /t:Build,Publish
  COMMENT "Building ${DOTNET_SAMPLE_CSPROJ}"
)

add_custom_target(Dotnet_Sample_Build ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${DOTNET_SAMPLE_OUTPUT_ASSEMBLY}
)

add_executable(Dotnet_Sample IMPORTED GLOBAL)
add_dependencies(Dotnet_Sample Dotnet_Build Dotnet_Sample_Build)

set_target_properties(Dotnet_Sample
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/publish/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_DOTNET_TARGET
)

add_custom_command(
  TARGET Dotnet_Sample_Build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
  TARGET Dotnet_Sample_Build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    ${CMAKE_CURRENT_BINARY_DIR}/publish
)

add_custom_command(
  TARGET Dotnet_Sample_Build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
  TARGET Dotnet_Sample_Build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    ${CMAKE_CURRENT_BINARY_DIR}/publish
)
