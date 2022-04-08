set(SOURCES
  main.cpp
)

add_executable(UIEventExample ${SOURCES})
add_dependencies(UIEventExample Resources)
target_link_libraries(UIEventExample
  PRIVATE
    Engine
)

if(NOVELRT_INCLUDE_CONAN_PATHS AND (WIN32 OR APPLE))
  add_dependencies(UIEventExample ThirdParty)
  copy_build_products(UIEventExample
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>

    DEPENDENCY ThirdParty
    TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>
  )
else()
  copy_build_products(UIEventExample
    DEPENDENCY Resources
    TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>/Resources

    DEPENDENCY Engine
    TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>
  )
endif()
