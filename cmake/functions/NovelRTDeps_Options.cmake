# Credit: https://github.com/diasurgical/devilutionX/blob/master/CMake/functions/dependency_options.cmake
# This function defines 3 options for finding and linking a dependency:
#
# 1. ${SYSTEM_OPTION_NAME}: whether to use the system version of the dependency (default: ${DEFAULT_SYSTEM_VALUE})
# 2. ${STATIC_OPTION_NAME}: whether to link the dependency statically.
#    The default is ON if ${SYSTEM_OPTION_NAME} is OFF or if target does not support shared libraries.
# 3. ${SHARED_OPTION_NAME}: whether to link the dependency dynamically.
#
# The ${LIB_NAME} argument is a human-readable library name only used in option description strings.
function(NovelRTDeps_Options LIB_NAME SYSTEM_OPTION_NAME DEFAULT_SYSTEM_VALUE STATIC_OPTION_NAME SHARED_OPTION_NAME)
  option(${SYSTEM_OPTION_NAME} "Use system-provided ${LIB_NAME}" ${DEFAULT_SYSTEM_VALUE})
  get_property(_supports_shared_libs GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)
  if(_supports_shared_libs)
    if(${SYSTEM_OPTION_NAME} OR ${SHARED_OPTION_NAME} OR ${NOVELRT_BUILD_SHARED_LIBS})
      set(_static_default OFF)
      set(_shared_default ON)
    else()
      set(_static_default ON)
      set(_shared_default OFF)
    endif()
    option(${STATIC_OPTION_NAME} "Link ${LIB_NAME} statically" ${_static_default})
    option(${SHARED_OPTION_NAME} "Link ${LIB_NAME} dynamically" ${_static_default})
  else()
    set(${STATIC_OPTION_NAME} ON)
    set(${STATIC_OPTION_NAME} ON PARENT_SCOPE)
  endif()

  if(${STATIC_OPTION_NAME})
    set(_msg_type "static")
  else()
    set(_msg_type "dynamic")
  endif()
  if(${SYSTEM_OPTION_NAME})
    set(_msg_source "system library")
  else()
    set(_msg_source "library from source")
  endif()
  message(STATUS "📚 ${LIB_NAME}: ${_msg_type} ${_msg_source}")
endfunction()
