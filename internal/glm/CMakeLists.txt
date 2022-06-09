include(FetchContent)

FetchContent_Declare(glm
        URL https://github.com/novelrt/glm/archive/refs/tags/0.9.9.8.zip
        URL_HASH SHA512=5db4901905ee78fa0abb5fa9116dd77790689ee0a833a6ea39a51e05bdad462ee7fb38b2a2b6d91e5b857ff9f6c70cc52841a02d0da181dd3470ecfbc11447ee

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

FetchContent_MakeAvailable(glm)
target_compile_definitions(glm INTERFACE BUILD_STATIC_LIBS=ON)