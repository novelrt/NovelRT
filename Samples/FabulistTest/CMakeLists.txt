set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(FabulistTest MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(FabulistTest
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.FabulistTest
      MACOS_BUNDLE_BUNDLE_NAME FabulistTest
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(FabulistTest ${SOURCES})
endif()
add_dependencies(FabulistTest Resources)
target_link_libraries(FabulistTest
  PRIVATE
    Engine
)

copy_build_products(FabulistTest
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:${APPLE}>,$<TARGET_FILE_DIR:FabulistTest>/../Resources,$<TARGET_FILE_DIR:FabulistTest>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(FabulistTest
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(FabulistTest)
else()
  copy_runtime_dependencies(FabulistTest
    DEPENDENCY Engine
  )
endif()
