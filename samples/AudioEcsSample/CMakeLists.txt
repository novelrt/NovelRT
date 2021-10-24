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