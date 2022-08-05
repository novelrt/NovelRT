set(SOURCES
  main.cpp
)

add_executable(AudioEcsSample ${SOURCES})
add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
  PRIVATE
    Engine
)
target_compile_definitions(AudioEcsSample PUBLIC ${NOVELRT_PLATFORM_COMPILE_DEFINITIONS})

copy_build_products(AudioEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>/Resources
)
CopyRuntimeDependencies(AudioEcsSample DEPENDENCY Engine)
