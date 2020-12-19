find_package(Dotnet ${Dotnet_VERSION} REQUIRED)

set(CSPROJ ${CMAKE_CURRENT_LIST_DIR}/NovelRT.DotNet.csproj)

set(OPTIONS
  /nologo
  /p:IntermediateOutputPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:MSBuildProjectExtensionsPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:OutDir=${CMAKE_CURRENT_BINARY_DIR}/
  /p:PublishDir=${CMAKE_CURRENT_BINARY_DIR}/publish/
)

execute_process(
  COMMAND ${DOTNET_EXECUTABLE} msbuild ${CSPROJ} ${OPTIONS}
    /t:Restore
)

execute_process(
  COMMAND ${DOTNET_EXECUTABLE} msbuild ${CSPROJ} ${OPTIONS}
    /t:GetCMakeOutputAssembly
  OUTPUT_VARIABLE OUTPUT_ASSEMBLY
)
string(STRIP "${OUTPUT_ASSEMBLY}" OUTPUT_ASSEMBLY)

execute_process(
  COMMAND ${DOTNET_EXECUTABLE} msbuild ${CSPROJ} ${OPTIONS}
    /t:GetCMakeOutputByproducts
  OUTPUT_VARIABLE OUTPUT_BYPRODUCTS
)
string(STRIP "${OUTPUT_BYPRODUCTS}" OUTPUT_BYPRODUCTS)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/publish)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_ASSEMBLY}
  BYPRODUCTS ${OUTPUT_BYPRODUCTS}
  COMMAND ${DOTNET_EXECUTABLE} msbuild ${CSPROJ} ${OPTIONS}
    /t:Build,Publish
  COMMENT "Building .NET subproject"
)

add_custom_target(dotnet_build
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_ASSEMBLY}
)

add_executable(Dotnet IMPORTED GLOBAL)
add_dependencies(Dotnet dotnet_build)
set_target_properties(Dotnet
  PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/publish/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_DOTNET_TARGET
)
