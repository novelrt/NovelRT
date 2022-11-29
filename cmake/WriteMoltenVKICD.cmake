function(write_moltenvk_icd_file TARGET)
    get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    list(APPEND filegen_snippet
    "
    execute_process(COMMAND echo \"Writing MoltenVK ICD file for ${TARGET} bundle...\")
    list(APPEND icd_snippet 
\"{
    \\\"file_format_version\\\" : \\\"1.0.0\\\",
    \\\"ICD\\\": {
        \\\"library_path\\\": \\\"@executable_path/../Frameworks/libMoltenVK.dylib\\\",
        \\\"api_version\\\" : \\\"1.2.0\\\",
        \\\"is_portability_driver\\\" : true
    }
}\")
    list(JOIN icd_snippet \"\\n\" icd_snippet)
    get_filename_component(icd_path \"$<TARGET_FILE_DIR:${TARGET}>\" DIRECTORY)
    if(NOT EXISTS \"\${icd_path}/Resources\")
        file(MAKE_DIRECTORY \"\${icd_path}/Resources\")
    endif()
    if(NOT EXISTS \"\${icd_path}/Resources/vulkan\")
        file(MAKE_DIRECTORY \"\${icd_path}/Resources/vulkan\")
    endif()
    if(NOT EXISTS \"\${icd_path}/Resources/vulkan/icd.d\")
        file(MAKE_DIRECTORY \"\${icd_path}/Resources/vulkan/icd.d\")
    endif()
    file(WRITE \${icd_path}/Resources/vulkan/icd.d/MoltenVK_icd.json \"\${icd_snippet}\")
    ")
    list(JOIN filegen_snippet "\n" filegen_snippet)
    file(GENERATE
        OUTPUT write_moltenvk_icd_file_for_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
        CONTENT "${filegen_snippet}")
    add_custom_command(TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -P write_moltenvk_icd_file_for_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
        DEPENDS ${TARGET}
    )
endfunction()