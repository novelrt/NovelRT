set(SOURCES
  main.cpp
)

add_executable(InputEcsSample ${SOURCES})
add_dependencies(InputEcsSample Resources)
target_link_libraries(InputEcsSample
  PRIVATE
    Engine
)

if(NOVELRT_INCLUDE_CONAN_PATHS AND (WIN32 OR APPLE))
  add_dependencies(InputEcsSample ThirdParty)
  copy_build_products(InputEcsSample
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>

    DEPENDENCY ThirdParty
    TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>
  )
else()
  copy_build_products(InputEcsSample
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>
  )
endif()
