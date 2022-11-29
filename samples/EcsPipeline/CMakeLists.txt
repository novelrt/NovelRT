set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(EcsPipeline MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(EcsPipeline 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.EcsPipeline
      MACOS_BUNDLE_BUNDLE_NAME EcsPipeline
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(EcsPipeline ${SOURCES})
endif()
add_dependencies(EcsPipeline Resources)
target_link_libraries(EcsPipeline
  PRIVATE
  Engine
)

copy_build_products(EcsPipeline
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:APPLE>,$<TARGET_FILE_DIR:EcsPipeline>/../Resources,$<TARGET_FILE_DIR:EcsPipeline>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(EcsPipeline
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(EcsPipeline)
else()
  copy_runtime_dependencies(EcsPipeline
    DEPENDENCY Engine
  )
endif()
