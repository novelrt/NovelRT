include(FetchContent)

FetchContent_Declare(glfw
        URL https://github.com/glfw/glfw/archive/refs/tags/3.3.7.zip
        URL_HASH SHA512=0ee020ddbbed783b5f0d271ee0a98b37fe489b633e0a8407821f12b2bcfc3b80645751076192b5224bfe1d26d6092c27af9a9bcd7953a419dcec0182e3716341

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

FetchContent_MakeAvailable(glfw)
