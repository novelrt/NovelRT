set(SOURCES
  main.cpp
  )

add_executable(EcsPipeline ${SOURCES})
add_dependencies(EcsPipeline Dotnet Resources)
target_link_libraries(EcsPipeline
  PRIVATE
  Engine
  )

add_custom_command(
  TARGET EcsPipeline POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  $<TARGET_FILE_DIR:Dotnet>
  $<TARGET_FILE_DIR:EcsPipeline>/dotnet
  )

copy_build_products(EcsPipeline
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/Resources

  DEPENDENCY Engine
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>

  DEPENDENCY Dotnet
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/dotnet
  CONDITION NOVELRT_INCLUDE_INK

  DEPENDENCY Dotnet
  DEPENDENCY_FILES nethost.dll
  TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>
  CONDITION NOVELRT_INCLUDE_INK AND WIN32
  )
