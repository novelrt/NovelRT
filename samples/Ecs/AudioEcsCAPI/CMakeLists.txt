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

copy_build_products(AudioEcsCAPI
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsCAPI>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsCAPI>

  DEPENDENCY Interop
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsCAPI>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsCAPI>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsCAPI>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)

if(NOVELRT_INCLUDE_INK)
  add_dependencies(AudioEcsCAPI Dotnet)
  target_compile_definitions(AudioEcsCAPI PRIVATE NOVELRT_INK)
endif()
