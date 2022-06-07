include(FetchContent)

FetchContent_Declare(crossguid
        URL https://github.com/graeme-hill/crossguid/archive/refs/tags/v0.2.2.zip
        URL_HASH SHA512=81b93f242c6c03dca5f96a9e070b4bce209c207147f3ba86c959abb235ba0a8a8778e0dc6bbf0f0012a880213c4c8685d393fa0053cfc196c64568e87d64a1c9

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

FetchContent_MakeAvailable(crossguid)
