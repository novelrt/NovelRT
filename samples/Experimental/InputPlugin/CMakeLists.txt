set(SOURCES
        main.cpp
        )

add_executable(InputPlugin ${SOURCES})
add_dependencies(InputPlugin Dotnet Resources)
target_link_libraries(InputPlugin
        PRIVATE
        Engine
        )

add_custom_command(
        TARGET InputPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Dotnet>
        $<TARGET_FILE_DIR:InputPlugin>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
    add_custom_command(
            TARGET InputPlugin POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE_DIR:InputPlugin>/dotnet/nethost.dll
            $<TARGET_FILE_DIR:InputPlugin>
    )
endif()

add_custom_command(
        TARGET InputPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Resources>
        $<TARGET_FILE_DIR:InputPlugin>/Resources
)

add_custom_command(
        TARGET InputPlugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Engine>
        $<TARGET_FILE_DIR:InputPlugin>
)
