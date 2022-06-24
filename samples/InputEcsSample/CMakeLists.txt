set(SOURCES
        main.cpp
        )

add_executable(InputEcsSample ${SOURCES})
add_dependencies(InputEcsSample Resources)
target_link_libraries(InputEcsSample
        PRIVATE
        Engine
        )
target_compile_definitions(InputEcsSample PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:NOVELRT_MOLTENVK_VENDORED>,1,0>)

copy_build_products(InputEcsSample
        DEPENDENCY Resources
        TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>/Resources

        DEPENDENCY Engine
        TARGET_LOCATION $<TARGET_FILE_DIR:InputEcsSample>
        )
