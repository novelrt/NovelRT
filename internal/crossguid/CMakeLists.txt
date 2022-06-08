include(FetchContent)

FetchContent_Declare(CrossGuid
        URL https://github.com/novelrt/crossguid/archive/refs/tags/v0.2.4-alpha.zip
        URL_HASH SHA512=114da82ecb1061c51c27729c687ac90f370f14e0b10de9439605153079646ddf3af9d2afde511f704c30e79e93f622ee31ed3bc4dd7fa2339629763440e02eca

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

FetchContent_MakeAvailable(CrossGuid)
