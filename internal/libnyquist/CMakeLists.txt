include(FetchContent)
message(STATUS "Fetching libnyquist")

FetchContent_Declare(nyquist
        URL https://github.com/ddiakopoulos/libnyquist/archive/e8c2985903d55b53ad3c1b86438de90f76c8628c.zip
        URL_HASH SHA512=e90f053f5e757eddfdd374bac36474f4796025d8d0e2c1d7f045d6aa3338738b43ec85b82b835d383f06ccbee2543ac68d5a75ec9d8f5b52ff3443c2ec51acda

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        TMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp"
        STAMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/stamp"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/dl"
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/src"
        SUBBUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build"
        INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/inst"
        LOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/log"
)

set(LIBNYQUIST_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(BUILD_LIBOPUS OFF CACHE INTERNAL "")
set(BUILD_LIBWAVPACK OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nyquist)
set_property(TARGET libnyquist PROPERTY POSITION_INDEPENDENT_CODE ON)
install(EXPORT libnyquist
  DESTINATION lib
  NAMESPACE libnyquist::)
install(TARGETS libnyquist
  EXPORT libnyquist
  LIBRARY DESTINATION lib)
