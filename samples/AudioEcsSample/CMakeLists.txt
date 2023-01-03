set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(AudioEcsSample MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(AudioEcsSample
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.AudioEcsSample
      MACOS_BUNDLE_BUNDLE_NAME AudioEcsSample
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(AudioEcsSample ${SOURCES})
endif()

add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
  PRIVATE
    Engine
)

copy_build_products(AudioEcsSample
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:${APPLE}>,$<TARGET_FILE_DIR:AudioEcsSample>/../Resources,$<TARGET_FILE_DIR:AudioEcsSample>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(AudioEcsSample
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(AudioEcsSample)
else()
  copy_runtime_dependencies(AudioEcsSample
    DEPENDENCY Engine
  )
endif()

