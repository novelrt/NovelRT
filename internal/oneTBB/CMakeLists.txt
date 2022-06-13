# TBB_DIR needs to be set to the path where the TBBConfig.cmake files are located.
# Without this, we'll have to assume that TBB needs to be located using the ONEAPI_ROOT variable
# We can also allow users to specify NOVELRT_TBB_PATH which should be the "tbb" folder inside of
# the oneAPI installation - this is the equivalent of TBBROOT as well.
message(STATUS "Locating oneTBB")

if(NOT DEFINED TBB_DIR)
  if(DEFINED ENV{ONEAPI_ROOT})
    set(TBB_DIR "$ENV{ONEAPI_ROOT}/tbb/latest/lib/cmake")
  elseif(DEFINED ENV{TBBROOT})
    set(TBB_DIR "$ENV{TBBROOT}/latest/lib/cmake")
  elseif(DEFINED NOVELRT_TBB_PATH)
    set(TBB_DIR "${NOVELRT_TBB_PATH}/latest/lib/cmake")
  else()
    message(FATAL_ERROR "Could not find oneTBB directory! Please define path to oneTBB via NOVELRT_TBB_PATH or the explicit TBB_DIR variables.")
  endif()
endif()

message(STATUS "Found oneTBB installation")
set(TBB_FIND_RELEASE_ONLY TRUE)
