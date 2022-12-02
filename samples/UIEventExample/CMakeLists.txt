set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(UIEventExample MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(UIEventExample 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.UIEventExample
      MACOS_BUNDLE_BUNDLE_NAME UIEventExample
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(UIEventExample ${SOURCES})
endif()
add_dependencies(UIEventExample Resources)
target_link_libraries(UIEventExample
  PRIVATE
    Engine
)

copy_build_products(UIEventExample
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:APPLE>,$<TARGET_FILE_DIR:UIEventExample>/../Resources,$<TARGET_FILE_DIR:UIEventExample>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(UIEventExample
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(UIEventExample)
else()
  copy_runtime_dependencies(UIEventExample
    DEPENDENCY Engine
  )
endif()
