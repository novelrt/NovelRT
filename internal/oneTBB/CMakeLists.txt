include(FetchContent)
message(STATUS "Fetching oneTBB")
set(TBB_TEST OFF CACHE BOOL "Build TBB Tests" FORCE)
set(TBBMALLOC_BUILD OFF CACHE BOOL "Build tbbmalloc" FORCE)

FetchContent_Declare(TBB
  URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v${NOVELRT_ONETBB_VERSION}.zip
  URL_HASH SHA512=fde7eb56b46fa86b619eb60e587728d19f31639ec06dfd5d7af0dab00ffba38606d7a89dcf050c4cdfa8896560a7424a3431619108f395348dadf60ad6b67a1b

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
  STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
  DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
  SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
  LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

  CONFIGURE_COMMAND "${CMAKE_COMMAND} -S ${CMAKE_CURRENT_BINARY_DIR}/src -B ${CMAKE_CURRENT_BINARY_DIR}/build"
  INSTALL_COMMAND "${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/build --prefix \"${CMAKE_CURRENT_BINARY_DIR}/inst\""
)

FetchContent_GetProperties(TBB)
if(NOT TBB_POPULATED)
  FetchContent_Populate(TBB)

  # Manually change the output directory so folders don't spawn randomly in the build env
  # This gets appended to "${CMAKE_BINARY_DIR}/" so we want to redirect it back into the
  # internal folder without modifying the logic too much.
  file(RELATIVE_PATH output_location "${CMAKE_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/build")
  set(TBB_OUTPUT_DIR_BASE "${output_location}/" CACHE INTERNAL "Set output directory for oneTBB")

  # Workaround to force oneTBB to build shared and not always export symbols
  # Causes failures during builds so we forcefully change these for oneTBB only
  # Credit: https://stackoverflow.com/a/62103349
  set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS_OLD ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS})
  # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF CACHE INTERNAL "Don't export symbols for Windows")
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
  # Set the values back to what they originally were
  set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS_OLD} CACHE BOOL "Tell CMake to always export symbols on Windows" FORCE)
endif()
