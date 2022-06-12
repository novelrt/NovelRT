include(FetchContent)
include(FindGit)
if(NOT GIT_FOUND)
  message(FATAL "Git is required to fetch and build oneTBB properly!")
endif()
# set(TBB_TEST OFF CACHE BOOL "" FORCE)

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

        PATCH_COMMAND git apply --ignore-space-change --ignore-whitespace "${CMAKE_CURRENT_LIST_DIR}/v202150-01.patch" "${CMAKE_CURRENT_LIST_DIR}/v202150-02.patch" "${CMAKE_CURRENT_LIST_DIR}/v202150-03.patch" "${CMAKE_CURRENT_LIST_DIR}/v202150-04.patch" "${CMAKE_CURRENT_LIST_DIR}/v202150-05.patch"
        )
FetchContent_MakeAvailable(TBB)
#set(TBB_FIND_RELEASE_ONLY ON CACHE BOOL "")
#add_definitions(-DGSL_USE_STATIC_CONSTEXPR_WORKAROUND=1)


