include(ExternalProject)
message(STATUS "Fetching MoltenVK")
message(WARNING 
        "NovelRT is set to build MoltenVK which can take upwards " 
        "of 30+ minutes on certain devices. Also, building MoltenVK "
        "requires that 'xcodebuild' is set as the default tool in xcode-select, "
        "and that the XCode Licence Agreements have been accepted. Otherwise, "
        "building MoltenVK will fail. Please make any changes prior to building "
        "NovelRT to ensure a smoother experience."
)

ExternalProject_Add(moltenvk
        URL https://github.com/KhronosGroup/MoltenVK/archive/refs/tags/v1.1.10.tar.gz
        URL_HASH SHA512=d712ffcbdd55d91d3ae2e2b7302838d98fdcd185e078a6a6c0337a08e257443d05b0c529d678fab69ff2c66608fde23d978604aed2052a52231c97416209b2d8

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
