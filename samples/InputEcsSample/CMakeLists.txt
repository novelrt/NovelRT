set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(InputEcsSample MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(InputEcsSample 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.InputEcsSample
      MACOS_BUNDLE_BUNDLE_NAME InputEcsSample
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(InputEcsSample ${SOURCES})
endif()
add_dependencies(InputEcsSample Resources)
target_link_libraries(InputEcsSample
  PRIVATE
    Engine
)

copy_build_products(InputEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources
)
copy_runtime_dependencies(InputEcsSample
  DEPENDENCY Engine
)
