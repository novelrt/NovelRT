find_package(Lua 5.3 REQUIRED)

add_library(Lua::Lua UNKNOWN IMPORTED)
set_target_properties(Lua::Lua
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${LUA_MATH_LIBRARY}"
    IMPORTED_LOCATION "${LUA_LIBRARY}"
)

set(CAPI_SOURCES
  main.c
)

set_source_files_properties(${CAPI_SOURCES} PROPERTIES LANGUAGE C)

add_executable(CAPI ${CAPI_SOURCES})
add_dependencies(CAPI Dotnet Resources)
target_link_libraries(CAPI
  PRIVATE
    Engine
    Interop
    Lua::Lua
)

add_custom_command(
  TARGET CAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Dotnet>
    $<TARGET_FILE_DIR:CAPI>/dotnet
)

if(WIN32)
  add_custom_command(
    TARGET CAPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_FILE_DIR:CAPI>/dotnet/nethost.dll
      $<TARGET_FILE_DIR:CAPI>
  )
endif()

add_custom_command(
  TARGET CAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:CAPI>/Resources
)

add_custom_command(
  TARGET CAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:CAPI>
)

add_custom_command(
  TARGET CAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    $<TARGET_FILE_DIR:CAPI>
)