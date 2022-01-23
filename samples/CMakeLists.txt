add_subdirectory(Experimental)
add_subdirectory(EcsPipeline)

if(NOVELRT_INCLUDE_INK)
  add_subdirectory(NovelRT.DotNet.Sample)
endif()
