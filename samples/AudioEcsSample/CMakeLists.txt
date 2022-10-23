if(NOVELRT_VULKAN_SDK)
  find_package(Vulkan REQUIRED)
endif()

set(SOURCES
        main.cpp
        )

add_executable(AudioEcsSample ${SOURCES})
add_dependencies(AudioEcsSample Resources)
target_link_libraries(AudioEcsSample
        PRIVATE
        Engine
        )
target_compile_definitions(AudioEcsSample PUBLIC -DNOVELRT_MOLTENVK_VENDORED=$<IF:$<BOOL:${NOVELRT_MOLTENVK_VENDORED}>,1,0>)

copy_build_products(AudioEcsSample
        DEPENDENCY Resources
        TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>/Resources

        DEPENDENCY Engine
        TARGET_LOCATION $<TARGET_FILE_DIR:AudioEcsSample>
        )
