set(SOURCES
  main.cpp
)

add_executable(AudioEcsSample ${SOURCES})
add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
  PRIVATE
    Engine
)
#target_compile_definitions(AudioEcsSample PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:${NOVELRT_MOLTENVK_VENDORED}>,1,0>)

copy_build_products(AudioEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>/Resources
)
copy_runtime_dependencies(AudioEcsSample
  DEPENDENCY Engine
)
