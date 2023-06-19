set(PLATFORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/platforms")

if(NOT NOVELRT_TARGET IN_LIST NOVELRT_TARGET_OPTIONS)
  message(FATAL_ERROR "Could not identify a proper target to build NovelRT for!")
else()
  list(FIND NOVELRT_TARGET_OPTIONS ${NOVELRT_TARGET} index)
  if(index EQUAL 0) # "Win32"
    include(${PLATFORMS_DIR}/windows.cmake)
  elseif(index EQUAL 1) # "Linux"
    include(${PLATFORMS_DIR}/linux.cmake)
  elseif(index EQUAL 2) # "macOS"
    include(${PLATFORMS_DIR}/macos.cmake)
  endif()
endif()


