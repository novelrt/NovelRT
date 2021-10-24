set(SOURCES
        main.cpp
        )

add_executable(VulkanRender ${SOURCES})
add_dependencies(VulkanRender Resources)
target_link_libraries(VulkanRender
        PRIVATE
        Engine
        )

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
