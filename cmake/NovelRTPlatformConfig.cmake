if(NOT NOVELRT_TARGET IN NOVELRT_TARGET_OPTIONS)
  message(FATAL_ERROR "Could not identify a proper target to build NovelRT for!")
else()
  list(FIND NOVELRT_TARGET_OPTIONS ${NOVELRT_TARGET} index)
  if(index EQUAL 0) # "Win32"
    include(platforms/windows.cmake)
  elseif(index EQUAL 1) # "Linux"
    include(platforms/linux.cmake)
  elseif(index EQUAL 2) # "macOS"
    include(platforms/macos.cmake)
  endif()
endif()


