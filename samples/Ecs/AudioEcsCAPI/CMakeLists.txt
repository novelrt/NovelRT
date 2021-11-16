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
