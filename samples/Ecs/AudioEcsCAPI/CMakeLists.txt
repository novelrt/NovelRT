set(SOURCES
  main.c
)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

add_executable(AudioEcsCAPI ${SOURCES})
add_dependencies(AudioEcsCAPI Resources)
target_link_libraries(AudioEcsCAPI
  PRIVATE
    Engine
    Interop
)

add_custom_command(
  TARGET AudioEcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:AudioEcsCAPI>/Resources
)

add_custom_command(
  TARGET AudioEcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:AudioEcsCAPI>
)

add_custom_command(
  TARGET AudioEcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    $<TARGET_FILE_DIR:AudioEcsCAPI>
)

if(NOVELRT_INCLUDE_INK)
    add_dependencies(AudioEcsCAPI Dotnet)
    target_compile_definitions(AudioEcsCAPI PRIVATE NOVELRT_INK)
    add_custom_command(
            TARGET AudioEcsCAPI POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:Dotnet>
            $<TARGET_FILE_DIR:AudioEcsCAPI>/dotnet
    )

    if(WIN32)
        add_custom_command(
                TARGET AudioEcsCAPI POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE_DIR:AudioEcsCAPI>/dotnet/nethost.dll
                $<TARGET_FILE_DIR:AudioEcsCAPI>
        )
    endif()
endif()