set(DOTEST_SOURCES
    DoTest.cpp
)

add_library(DoTest SHARED ${DOTEST_SOURCES})
add_dependencies(DoTest Engine)
target_compile_features(DoTest PUBLIC cxx_std_17)

add_custom_command(
  TARGET DoTest POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/tests/DoTest/testlibconf.json  
    $<TARGET_FILE_DIR:DoTest>
    
)

target_link_libraries(DoTest Engine)