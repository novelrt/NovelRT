macro(CopyRuntimeDependencies)
  set(TARGET ${SOURCE})
  foreach(SOURCE IN ITEMS ${ARGV})
  list(FIND ${ARGV} ${SOURCE} index)
  if(WIN32 AND index NOT EQUAL 0)
  add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${SOURCE}> $<TARGET_FILE_DIR:${TARGET}>
    COMMAND_EXPAND_LISTS
  )
  endif()
  endforeach()
  add_custom_command(
    TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
    COMMAND_EXPAND_LISTS
  )
endmacro()
