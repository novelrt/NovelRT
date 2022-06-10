include(FetchContent)

FetchContent_Declare(jsoncons
        URL https://github.com/danielaparker/jsoncons/archive/refs/tags/v0.168.7.zip
        URL_HASH SHA512=610f30b8a388c3f865d7dfd1444168f2e3a1a93c02545f54f5bb535467346159aeb0d2746b797cf34d165bb8dfb878e27829469470bc5af93904d66669fc4692

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
        )
set(JSONCONS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(jsoncons)
