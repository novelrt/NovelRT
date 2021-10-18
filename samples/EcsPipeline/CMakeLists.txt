set(SOURCES
        main.cpp
        )

add_executable(EcsPipeline ${SOURCES})
add_dependencies(EcsPipeline Dotnet Resources)
target_link_libraries(EcsPipeline
        PRIVATE
        Engine
        )

add_custom_command(
        TARGET EcsPipeline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Dotnet>
        $<TARGET_FILE_DIR:EcsPipeline>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
    add_custom_command(
            TARGET EcsPipeline POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE_DIR:EcsPipeline>/dotnet/nethost.dll
            $<TARGET_FILE_DIR:EcsPipeline>
    )
endif()

add_custom_command(
        TARGET EcsPipeline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Resources>
        $<TARGET_FILE_DIR:EcsPipeline>/Resources
)

add_custom_command(
        TARGET EcsPipeline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Engine>
        $<TARGET_FILE_DIR:EcsPipeline>
)
