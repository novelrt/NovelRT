include(CMakeDependentOption)

cmake_dependent_option(NOVELRT_BUILD_SAMPLES_SCRIPTING_REPL "Build NovelRT Scripting REPL sample" ON "NOVELRT_BUILD_SAMPLES_SCRIPTING" OFF)

if(NOVELRT_BUILD_SAMPLES_SCRIPTING_REPL)
  add_subdirectory(REPL)
endif()
