find_package(Lua 5.3 REQUIRED)

add_library(Lua::Lua UNKNOWN IMPORTED)
set_target_properties(Lua::Lua
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${LUA_MATH_LIBRARY}"
    IMPORTED_LOCATION "${LUA_LIBRARY}"
)

set(SIMPLE_SOURCES
  main.cpp
)

add_executable(Simple ${SIMPLE_SOURCES})
add_dependencies(Simple Dotnet Resources)
target_link_libraries(Simple
  PRIVATE
    Engine
    Lua::Lua
)

add_custom_command(
  TARGET Simple POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Dotnet>
    $<TARGET_FILE_DIR:Simple>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
  add_custom_command(
    TARGET Simple POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_FILE_DIR:Simple>/dotnet/nethost.dll
      $<TARGET_FILE_DIR:Simple>
  )
endif()

add_custom_command(
  TARGET Simple POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:Simple>/Resources
)
