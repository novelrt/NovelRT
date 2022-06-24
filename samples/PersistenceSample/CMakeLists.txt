set(SOURCES
  main.cpp
  )

add_executable(PersistenceSample ${SOURCES})
add_dependencies(PersistenceSample Resources)
target_link_libraries(PersistenceSample
  PRIVATE
  Engine
  )
target_compile_definitions(PersistenceSample PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:NOVELRT_MOLTENVK_VENDORED>,1,0>)

copy_build_products(PersistenceSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:PersistenceSample>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:PersistenceSample>
  )
