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
  TARGET_LOCATION $<IF:$<BOOL:${APPLE}>,$<TARGET_FILE_DIR:InputEcsSample>/../Resources,$<TARGET_FILE_DIR:InputEcsSample>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(InputEcsSample
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(InputEcsSample)
else()
  copy_runtime_dependencies(InputEcsSample
    DEPENDENCY Engine
  )
endif()
