include(FetchContent)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(GSL_INSTALL ON)

FetchContent_MakeAvailable(GSL)

#install(
#        DIRECTORY ${GSL_SOURCE_DIR}/include/
#        DESTINATION include
#        PATTERN "CMakeLists.txt" EXCLUDE
#)
