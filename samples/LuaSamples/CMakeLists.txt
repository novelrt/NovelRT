find_package(Lua 5.3 REQUIRED)

add_library(Lua::Lua UNKNOWN IMPORTED)
set_target_properties(Lua::Lua
                      PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
                      INTERFACE_LINK_LIBRARIES "${LUA_MATH_LIBRARY}"
                      IMPORTED_LOCATION "${LUA_LIBRARY}"
                      )

set(LUA_SOURCES
    main.cpp
    )

add_executable(LuaSamples ${LUA_SOURCES})

target_link_libraries(LuaSamples
                      PRIVATE
                      Engine
                      Lua::Lua
                      )

add_custom_command(
    TARGET LuaSamples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:LuaSamples>/Resources
)
