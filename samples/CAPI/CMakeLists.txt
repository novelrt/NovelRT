find_package(lua 5.3 REQUIRED)

set(SOURCES
  main.c
)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

add_executable(CAPI ${SOURCES})
add_dependencies(CAPI Dotnet Resources)
target_link_libraries(CAPI
  PRIVATE
    Engine
    Interop
    lua::lua
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
