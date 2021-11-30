set(SOURCES
  main.cpp
)

add_executable(AudioEcsSample ${SOURCES})
add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
  PRIVATE
    Engine
)

add_custom_command(
  TARGET AudioEcsSample POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:AudioEcsSample>/Resources
)

add_custom_command(
  TARGET AudioEcsSample POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:AudioEcsSample>
)

if(NOVELRT_INCLUDE_INK)
    add_dependencies(AudioEcsSample Dotnet)
    target_compile_definitions(AudioEcsSample PRIVATE NOVELRT_INK)
    add_custom_command(
            TARGET AudioEcsSample POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:Dotnet>
            $<TARGET_FILE_DIR:AudioEcsSample>/dotnet
    )
    #this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
    if(WIN32)
        add_custom_command(
                TARGET AudioEcsSample POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE_DIR:AudioEcsSample>/dotnet/nethost.dll
                $<TARGET_FILE_DIR:AudioEcsSample>
        )
    endif()
endif()
