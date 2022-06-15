include(FetchContent)
message(STATUS "Fetching GLM")

FetchContent_Declare(glm
        URL https://github.com/novelrt/glm/archive/refs/heads/master.zip
        URL_HASH SHA512=c87d14dfd240633227bdf5e4b43dd5567e522a72a09cd888a34c8fa3d696ffac91d8d7f16abb5f3a4326d69bca69c4f33e8f9be54a32aedf3ffb32d14a6bf322

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
        )

FetchContent_MakeAvailable(glm)
install(
  DIRECTORY ${glm_SOURCE_DIR}/glm/
  DESTINATION include/glm
  PATTERN "CMakeLists.txt" EXCLUDE
)
