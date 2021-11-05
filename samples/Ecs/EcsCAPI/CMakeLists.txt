set(SOURCES
  main.c
)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

add_executable(EcsCAPI ${SOURCES})
add_dependencies(EcsCAPI Resources)
target_link_libraries(EcsCAPI
  PRIVATE
    Engine
    Interop
)

add_custom_command(
  TARGET EcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:EcsCAPI>/Resources
)

add_custom_command(
  TARGET EcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:EcsCAPI>
)

add_custom_command(
  TARGET EcsCAPI POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Interop>
    $<TARGET_FILE_DIR:EcsCAPI>
)
