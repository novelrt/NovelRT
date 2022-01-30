set(SOURCES
        main.cpp
        )

add_executable(InputPlugin ${SOURCES})
add_dependencies(InputPlugin Resources)
target_link_libraries(InputPlugin
        PRIVATE
        Engine
        )

copy_build_products(InputPlugin
        DEPENDENCY Resources
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>/Resources

        DEPENDENCY Engine
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>
        )
