include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_EXPERIMENTAL "Build NovelRT experimental samples" ON "NOVELRT_BUILD_SAMPLES" OFF)

add_subdirectory(Experimental)
#add_subdirectory(EcsPipeline)
#add_subdirectory(InputEcsSample)
#add_subdirectory(PersistenceSample)
#add_subdirectory(UIEventExample)
#add_subdirectory(FabulistTest)
#add_subdirectory(AudioEcsSample)
