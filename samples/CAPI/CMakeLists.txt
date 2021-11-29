include(CopyBuildProducts)

set(SOURCES
  main.c
)

set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

add_executable(CAPI ${SOURCES})
add_dependencies(CAPI Resources)
target_link_libraries(CAPI
  PRIVATE
    Engine
    Interop
)

copy_build_products(CAPI
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:CAPI>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:CAPI>

  DEPENDENCY Interop
  TARGET_LOCATION $<TARGET_FILE_DIR:CAPI>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:CAPI>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:CAPI>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
)

if(NOVELRT_INCLUDE_INK)
  add_dependencies(CAPI Dotnet)
  target_compile_definitions(CAPI PRIVATE NOVELRT_INK)
endif()

