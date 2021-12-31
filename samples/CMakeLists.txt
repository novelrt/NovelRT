add_subdirectory(Simple)
add_subdirectory(CAPI)
add_subdirectory(Experimental)
add_subdirectory(EcsPipeline)
add_subdirectory(Ecs)

if(NOVELRT_INCLUDE_INK)
  add_subdirectory(NovelRT.DotNet.Sample)
endif()
