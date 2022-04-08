set(SOURCES
  main.cpp
  )

add_executable(EcsPipeline ${SOURCES})
add_dependencies(EcsPipeline Resources)
target_link_libraries(EcsPipeline
  PRIVATE
  Engine
  )

if(NOVELRT_INCLUDE_CONAN_PATHS AND (WIN32 OR APPLE))
  add_dependencies(EcsPipeline ThirdParty)
  copy_build_products(EcsPipeline
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>

    DEPENDENCY ThirdParty
    TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>
  )
else()
  copy_build_products(EcsPipeline
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:EcsPipeline>
  )
endif()

