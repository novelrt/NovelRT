set(PLATFORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/platforms")

if(NOT NOVELRT_TARGET IN_LIST NOVELRT_TARGET_OPTIONS)
  message(FATAL_ERROR "Could not identify a proper target to build NovelRT for!")
else()
  if(${NOVELRT_TARGET} STREQUAL "Win32")
    include(${PLATFORMS_DIR}/windows.cmake)
  elseif(${NOVELRT_TARGET} STREQUAL "Linux")
    include(${PLATFORMS_DIR}/linux.cmake)
  elseif(${NOVELRT_TARGET} STREQUAL "macOS")
    include(${PLATFORMS_DIR}/macos.cmake)
  endif()
endif()


