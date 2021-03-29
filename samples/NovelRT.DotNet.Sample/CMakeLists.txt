find_package(Dotnet ${NOVELRT_DOTNET_VERSION} REQUIRED)

set(CSPROJ ${CMAKE_CURRENT_LIST_DIR}/NovelRT.DotNet.Sample.csproj)

set(SOURCES
  NovelRT.DotNet.Sample.runtimeconfig.json
  Program.cs
)

set(OPTIONS
  /nologo
  /p:IntermediateOutputPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Sample_Build.dir/obj/
  /p:MSBuildProjectExtensionsPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Sample_Build.dir/obj/
  /p:OutDir=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Sample_Build.dir/bin/
  /p:PublishDir=${CMAKE_CURRENT_BINARY_DIR}/
  /p:BuildingViaCMake=true
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
  /t:Restore
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
  /t:GetCMakeOutputAssembly
  OUTPUT_VARIABLE OUTPUT_ASSEMBLY
)
string(STRIP "${OUTPUT_ASSEMBLY}" OUTPUT_ASSEMBLY)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
  /t:GetCMakeOutputByproducts
  OUTPUT_VARIABLE OUTPUT_BYPRODUCTS
)
string(STRIP "${OUTPUT_BYPRODUCTS}" OUTPUT_BYPRODUCTS)

add_custom_command(
  OUTPUT ${OUTPUT_ASSEMBLY}
  DEPENDS ${SOURCES} ${CSPROJ}
  BYPRODUCTS ${OUTPUT_BYPRODUCTS}
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
  /t:Build,Publish
  COMMENT "Building ${CSPROJ}"
)

add_custom_target(Dotnet_Sample_Build ALL
  DEPENDS ${OUTPUT_ASSEMBLY}
)

add_executable(Dotnet_Sample IMPORTED GLOBAL)
add_dependencies(Dotnet_Sample Dotnet_Build Dotnet_Sample_Build)

set_target_properties(Dotnet_Sample
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_DOTNET_TARGET
)

add_custom_command(
  TARGET Dotnet_Sample_Build POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    ${CMAKE_CURRENT_BINARY_DIR}/Resources
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
    $<TARGET_FILE_DIR:Interop>
    ${CMAKE_CURRENT_BINARY_DIR}
)
