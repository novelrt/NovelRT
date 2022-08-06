add_subdirectory(NovelRT)
list(APPEND NOVELRT_EXPORTED_TARGETS Engine)
if (NOVELRT_BUILD_INTEROP)
    add_subdirectory(NovelRT.Interop)
    list(APPEND NOVELRT_EXPORTED_TARGETS Interop)
endif()

if(NOVELRT_INSTALL)
  install(
    TARGETS ${NOVELRT_EXPORTED_TARGETS}
    EXPORT NovelRTTargets
    DESTINATION lib
    RUNTIME DESTINATION bin
  )
  install(
    EXPORT NovelRTTargets
    FILE NovelRTTargets.cmake
    DESTINATION lib/cmake/NovelRT
  )
endif()


