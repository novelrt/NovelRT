# TBB_DIR needs to be set to the path where the TBBConfig.cmake files are located.
# Without this, we'll have to assume that TBB needs to be located using the ONEAPI_ROOT variable
# We can also allow users to specify NOVELRT_TBB_PATH which should be the "tbb" folder inside of
# the oneAPI installation - this is the equivalent of TBBROOT as well.
message(STATUS "Locating oneTBB")
set(NOVELRT_TBB_EXTERNAL ON)
if(NOT DEFINED TBB_DIR)
  if(DEFINED ENV{ONEAPI_ROOT})
    set(TBB_DIR "$ENV{ONEAPI_ROOT}/tbb/latest/lib/cmake")
  elseif(DEFINED ENV{TBBROOT})
    set(TBB_DIR "$ENV{TBBROOT}/latest/lib/cmake")
  elseif(DEFINED NOVELRT_TBB_PATH)
    set(TBB_DIR "${NOVELRT_TBB_PATH}/latest/lib/cmake")
  else()
    # Let's try to build the project ourselves
    message(STATUS "Fetching oneTBB")
    set(NOVELRT_TBB_EXTERNAL OFF)
    include(FetchContent)
    FetchContent_Declare(TBB
        URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip
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

        CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=ON -DTBB_TEST=OFF -DTBB_EXAMPLES=OFF -DTBBMALLOC_BUILD=OFF -DTBB_BENCH=OFF
        CONFIGURE_COMMAND "${CMAKE_COMMAND} -S ${CMAKE_CURRENT_BINARY_DIR}/src -B ${CMAKE_CURRENT_BINARY_DIR}/build"
        INSTALL_COMMAND "${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/build -prefix \"${CMAKE_CURRENT_BINARY_DIR}/inst\""
    )
    FetchContent_Populate(TBB)
    # Store the old value of the 'BUILD_SHARED_LIBS'
    set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
    # Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
    set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)



    # include(ExternalProject)
    # ExternalProject_Add(TBB
    #   URL https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip
    #   URL_HASH SHA512=fde7eb56b46fa86b619eb60e587728d19f31639ec06dfd5d7af0dab00ffba38606d7a89dcf050c4cdfa8896560a7424a3431619108f395348dadf60ad6b67a1b

    #   PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    #   TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
    #   STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
    #   DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
    #   SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
    #   BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
    #   INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
    #   LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

    #   CMAKE_ARGS -DBUILD_SHARED_LIBS=ON -DTBB_TEST=OFF -DTBB_EXAMPLES=OFF -DTBBMALLOC_BUILD=OFF -DTBB_BENCH=OFF -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    # )
  endif()
endif()

if(NOVELRT_TBB_EXTERNAL)
  message(STATUS "Found oneTBB installation")
endif()
