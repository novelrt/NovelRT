include(ExternalProject)
message(STATUS "Fetching MoltenVK")
message(WARNING 
        "NovelRT is set to build MoltenVK which can take upwards " 
        "of 30+ minutes on certain devices. Also, building MoltenVK "
        "requires that 'xcodebuild' is set as the default tool in xcode-select, "
        "and that the XCode Licence Agreements have been accepted. Otherwise, "
        "building MoltenVK will fail. Please make any changes prior to building "
        "NovelRT to ensure a smoother experience.")

ExternalProject_Add(moltenvk
        URL https://github.com/KhronosGroup/MoltenVK/archive/refs/tags/v1.1.6.tar.gz
        URL_HASH SHA512=854042934712cd6f30cd447a6d1cd35cc50a6abe405d1b33044e96cca3e05e9ab4fb7dc3f52c00dad5c1c87b59de59e88bd25575470e3159e83ade60884750c9

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"

        BUILD_IN_SOURCE ON
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        BUILD_COMMAND <SOURCE_DIR>/fetchDependencies "--macos" COMMAND xcodebuild build -quiet -project MoltenVKPackaging.xcodeproj -scheme "MoltenVK Package (macOS only)"
)

set(NOVELRT_MOLTENVK_DYLIB_PATH "${CMAKE_CURRENT_BINARY_DIR}/src/MoltenVK/dylib/macOS" CACHE STRING "Path to MoltenVK directory for generated ICD/Loader")
set(NOVELRT_MOLTENVK_LIB "${NOVELRT_MOLTENVK_DYLIB_PATH}/libMoltenVK.dylib" CACHE STRING "File path to MoltenVK library for NovelRT" FORCE)
set(NOVELRT_MOLTENVK_LIBTOCOPY "libMoltenVK.dylib" CACHE STRING "MoltenVK Library to be copied for NovelRT" FORCE)
set(NOVELRT_MOLTENVK_ICDTOCOPY "MoltenVK_icd.json" CACHE STRING "MoltenVK ICD to be copied for NovelRT" FORCE)
set(NOVELRT_MOLTENVK_VENDORED ON CACHE BOOL "MoltenVK is being vendored by the NovelRT project" FORCE)