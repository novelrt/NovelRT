find_package(Dotnet 3.1.100 REQUIRED)

set(CSPROJ ${CMAKE_CURRENT_LIST_DIR}/NovelRT.DotNet.csproj)

set(OPTIONS
  /nologo
  /p:IntermediateOutputPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:MSBuildProjectExtensionsPath=${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:OutDir=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/Dotnet_Build.dir/
  /p:PublishDir=${CMAKE_CURRENT_BINARY_DIR}/
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
    /t:Restore
)

execute_process(
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
    /t:GetCMakeOutputByproducts
  OUTPUT_VARIABLE OUTPUT_BYPRODUCTS
)
string(STRIP "${OUTPUT_BYPRODUCTS}" OUTPUT_BYPRODUCTS)

add_custom_command(
  OUTPUT ${OUTPUT_BYPRODUCTS}
  DEPENDS ${CSPROJ}
  COMMAND ${Dotnet_PROGRAM} msbuild ${CSPROJ} ${OPTIONS}
    /t:Build,Publish
  VERBATIM
  COMMENT "Building .NET subproject"
)

add_custom_target(Dotnet_Build
  DEPENDS ${OUTPUT_BYPRODUCTS})

if(WIN32)
  set(nethost_lib "nethost.dll")
elseif(APPLE)
  set(nethost_lib "libnethost.dylib")
elseif(UNIX)
  set(nethost_lib "libnethost.so")
endif()

add_library(Dotnet SHARED IMPORTED GLOBAL)
add_dependencies(Dotnet Dotnet_Build)
set_target_properties(Dotnet
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}"
    IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/${nethost_lib}"
    IMPORTED_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/nethost.h"
    ADDITIONAL_COPY_LOCAL_FILES "${OUTPUT_BYPRODUCTS}"
    ADDITIONAL_COPY_LOCAL_FILES_DESTINATION Dotnet
)

if(WIN32)
  set_target_properties(Dotnet
    PROPERTIES
      IMPORTED_IMPLIB "${CMAKE_CURRENT_BINARY_DIR}/nethost.lib"
  )
elseif(UNIX AND NOT APPLE)
  set_target_properties(Dotnet
    PROPERTIES
      INTERFACE_LINK_LIBRARIES "dl"
  )
endif()
