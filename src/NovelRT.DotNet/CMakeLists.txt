find_package(Dotnet ${NOVELRT_DOTNET_VERSION} REQUIRED)

set(CSPROJ ${CMAKE_CURRENT_LIST_DIR}/NovelRT.DotNet.csproj)

set(SOURCES
  NovelRT.DotNet.runtimeconfig.json

  InkService.cs
  InkService.Exports.cs
  RuntimeService.cs
  RuntimeService.Exports.cs

  Interop/NativeTypeName.cs

  Interop/Animation/NovelRT.cs
  Interop/Animation/NrtAnimatorPlayState.cs

  Interop/Audio/NovelRT.cs

  Interop/Core/NovelRT.cs
  Interop/Core/NrtBool.cs
  Interop/Core/NrtLogLevel.cs
  Interop/Core/NrtResult.cs

  Interop/DotNet/NovelRT.cs

  Interop/Ecs/NovelRT.cs

  Interop/Graphics/NovelRT.cs
  Interop/Graphics/NrtCameraFrameState.cs

  Interop/Ink/NovelRT.cs

  Interop/Input/NovelRT.cs
  Interop/Input/NrtKeyCode.cs
  Interop/Input/NrtKeyState.cs

  Interop/Maths/NovelRT.cs
  Interop/Maths/NrtGeoBounds.cs
  Interop/Maths/NrtGeoMatrix4x4F.cs
  Interop/Maths/NrtGeoVector2F.cs
  Interop/Maths/NrtGeoVector3F.cs
  Interop/Maths/NrtGeoVector4F.cs
  Interop/Maths/NrtTransform.cs

  Interop/SceneGraph/NovelRT.cs

  Interop/Timing/NovelRT.cs

  Interop/Utilities/NovelRT.cs

  Interop/Windowing/NovelRT.cs
  Interop/Windowing/NrtWindowMode.cs
)

set(OPTIONS
  /nologo
  /p:IntermediateOutputPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:MSBuildProjectExtensionsPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:OutDir=${CMAKE_CURRENT_BINARY_DIR}/
  /p:PublishDir=${CMAKE_CURRENT_BINARY_DIR}/publish/
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

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/publish)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_ASSEMBLY}
  DEPENDS ${SOURCES} ${CSPROJ}
  BYPRODUCTS ${OUTPUT_BYPRODUCTS}
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
  /t:Build,Publish
  COMMENT "Building ${CSPROJ}"
)

add_custom_target(Dotnet_Build ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_ASSEMBLY}
)

add_executable(Dotnet IMPORTED GLOBAL)
add_dependencies(Dotnet Dotnet_Build)
set_target_properties(Dotnet
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/publish/IF_YOU_SEE_THIS_YOU_TRIED_TO_RUN_THE_DOTNET_TARGET
)

if(WIN32)
  set(nethost_lib "nethost.dll")
elseif(APPLE)
  set(nethost_lib "libnethost.dylib")
elseif(UNIX)
  set(nethost_lib "libnethost.so")
endif()

add_library(CoreCLR::nethost SHARED IMPORTED GLOBAL)
set_target_properties(CoreCLR::nethost
  PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/publish"
  IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/publish/${nethost_lib}"
  )

if(WIN32)
  set_target_properties(CoreCLR::nethost
    PROPERTIES
    IMPORTED_IMPLIB "${CMAKE_CURRENT_BINARY_DIR}/publish/nethost.lib"
    )
  # TODO: check if this is necessary on OS X too
elseif(UNIX AND NOT APPLE)
  set_target_properties(CoreCLR::nethost
    PROPERTIES
    INTERFACE_LINK_LIBRARIES "dl"
    )
endif()
