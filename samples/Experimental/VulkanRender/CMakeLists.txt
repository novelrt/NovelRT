set(SOURCES
  main.cpp
)

if(APPLE)
  add_executable(VulkanRender MACOSX_BUNDLE ${NOVELCHAN_ICON} ${SOURCES})
  set_target_properties(VulkanRender 
    PROPERTIES
      BUNDLE True
      MACOSX_BUNDLE_GUI_IDENTIFIER dev.novelrt.samples.VulkanRender
      MACOS_BUNDLE_BUNDLE_NAME VulkanRender
      MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
      MACOSX_BUNDLE_SHORT_VERION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  )
else()
  add_executable(VulkanRender ${SOURCES})
endif()
add_dependencies(VulkanRender Resources)
target_link_libraries(VulkanRender
  PRIVATE
    Engine
)

copy_build_products(VulkanRender
  DEPENDENCY Resources
  TARGET_LOCATION $<IF:$<BOOL:APPLE>,$<TARGET_FILE_DIR:VulkanRender>/../Resources,$<TARGET_FILE_DIR:VulkanRender>/Resources>
)

if(APPLE)
  copy_runtime_dependencies(VulkanRender
    DEPENDENCY Engine
    LIBRARY Vulkan::MoltenVK
    LIBRARY Vorbis::vorbisenc
    LIBRARY Vorbis::vorbis
    LIBRARY FLAC::FLAC
    LIBRARY Opus::opus
    LIBRARY Ogg::ogg
    LIBRARY ZLIB::zlib
  )
  write_moltenvk_icd_file(VulkanRender)
else()
  copy_runtime_dependencies(VulkanRender
    DEPENDENCY Engine
  )
endif()
