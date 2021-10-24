add_subdirectory(Simple)
add_subdirectory(CAPI)
add_subdirectory(Experimental)
add_subdirectory(AudioEcsSample)

if(NOVELRT_INCLUDE_INK)
  add_subdirectory(NovelRT.DotNet.Sample)
endif()
