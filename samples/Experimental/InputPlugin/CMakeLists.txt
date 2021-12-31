set(SOURCES
        main.cpp
        )

add_executable(InputPlugin ${SOURCES})
add_dependencies(InputPlugin Dotnet Resources)
target_link_libraries(InputPlugin
        PRIVATE
        Engine
        )

copy_build_products(InputPlugin
        DEPENDENCY Resources
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>/Resources

        DEPENDENCY Engine
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>

        DEPENDENCY Dotnet
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>/dotnet
        CONDITION NOVELRT_INCLUDE_INK

        DEPENDENCY Dotnet
        DEPENDENCY_FILES nethost.dll
        TARGET_LOCATION $<TARGET_FILE_DIR:InputPlugin>
        CONDITION NOVELRT_INCLUDE_INK AND WIN32
        )
