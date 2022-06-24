set(SOURCES
        main.cpp
        )

add_executable(UIEventExample ${SOURCES})
add_dependencies(UIEventExample Resources)
target_link_libraries(UIEventExample
        PRIVATE
        Engine
        )
target_compile_definitions(UIEventSample PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:NOVELRT_MOLTENVK_VENDORED>,1,0>)

copy_build_products(UIEventExample
        DEPENDENCY Resources
        TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>/Resources

        DEPENDENCY Engine
        TARGET_LOCATION $<TARGET_FILE_DIR:UIEventExample>
        )
