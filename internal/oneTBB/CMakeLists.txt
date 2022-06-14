include(FetchContent)
message(STATUS "Fetching oneTBB")

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

        CONFIGURE_COMMAND "${CMAKE_COMMAND} -S ${CMAKE_CURRENT_BINARY_DIR}/src -B ${CMAKE_CURRENT_BINARY_DIR}/build"
        INSTALL_COMMAND "${CMAKE_COMMAND} --install ${CMAKE_CURRENT_BINARY_DIR}/build --prefix \"${CMAKE_CURRENT_BINARY_DIR}/inst\""
)
FetchContent_Populate(TBB)
# Store the old value of the 'BUILD_SHARED_LIBS'
set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
# Make subproject to use 'BUILD_SHARED_LIBS=ON' setting.
set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build SHARED libraries")
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD} CACHE BOOL "Type of libraries to build" FORCE)
set(TBB_TEST OFF CACHE BOOL "Build TBB Tests" FORCE)
set(TBBMALLOC_BUILD OFF CACHE BOOL "Build tbbmalloc" FORCE)
