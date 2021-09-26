set(SOURCES
        main.cpp
        )

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Dotnet Resources)
target_link_libraries(VulkanRender
        PRIVATE
        Engine
        )

add_custom_command(
        TARGET VulkanRender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Dotnet>
        $<TARGET_FILE_DIR:VulkanRender>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
    add_custom_command(
            TARGET VulkanRender POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE_DIR:VulkanRender>/dotnet/nethost.dll
            $<TARGET_FILE_DIR:VulkanRender>
    )
endif()

add_custom_command(
        TARGET VulkanRender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Resources>
        $<TARGET_FILE_DIR:VulkanRender>/Resources
)

add_custom_command(
        TARGET VulkanRender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:Engine>
        $<TARGET_FILE_DIR:VulkanRender>
)
