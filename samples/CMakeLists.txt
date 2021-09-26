add_subdirectory(Simple)
add_subdirectory(CAPI)
add_subdirectory(Experimental)

if(NOVELRT_INCLUDE_INK)
  add_subdirectory(NovelRT.DotNet.Sample)
endif()
