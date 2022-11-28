set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(PersistenceSample MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(PersistenceSample 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.PersistenceSample
      MACOS_BUNDLE_BUNDLE_NAME PersistenceSample
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(PersistenceSample ${SOURCES})
endif()
add_dependencies(PersistenceSample Resources)
target_link_libraries(PersistenceSample
  PRIVATE
    Engine
)

copy_build_products(PersistenceSample
  DEPENDENCY Resources
  TARGET_LOCATION $<TARGET_FILE_DIR:PersistenceSample>/Resources
)
copy_runtime_dependencies(PersistenceSample
  DEPENDENCY Engine
)
