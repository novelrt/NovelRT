if(WIN32)
  include(platforms/windows)
endif()

if(APPLE)
  include(platforms/macos)
endif()
