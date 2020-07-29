#TODO: this won't be here in final PR, just using it for testing

set(DOTEST_SOURCES
    DoTest.cpp
)

add_library(DoTest MODULE ${DOTEST_SOURCES})
add_dependencies(DoTest Engine)
target_compile_features(DoTest PUBLIC cxx_std_17)
target_include_directories(DoTest
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(DoTest Engine)