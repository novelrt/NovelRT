function(write_moltenvk_icd_file TARGET)
    get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    list(APPEND filegen_snippet
    "
    list(APPEND icd_snippet \"{
        \\\"file_format_version\\\" : \\\"1.0.0\\\",
        \\\"ICD\\\": {
            \\\"library_path\\\": \\\"@executable_path/../Frameworks/libMoltenVK.dylib\\\",
            \\\"api_version\\\" : \\\"1.1.0\\\",
            \\\"is_portability_driver\\\" : true
        }
    }\")
    list(JOIN icd_snippet \"\\n\" icd_snippet)

    file(GENERATE
        OUTPUT $<TARGET_FILE_DIR:${TARGET}>/../Resources/vulkan/icd.d/MoltenVK_icd.json
        CONTENT \"${icd_snippet}\")
    ")
    list(JOIN filegen_snippet "\n" filegen_snippet)
    file(GENERATE
        OUTPUT write_moltenvk_icd_file_for_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
        CONTENT "${filegen_snippet}"))
    add_custom_command(TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Writing MoltenVK ICD file for macOS bundle..."
        COMMAND ${CMAKE_COMMAND} -P write_moltenvk_icd_file_for_${TARGET}$<$<BOOL:${multi_config}>:_$<CONFIG>>.cmake
        DEPENDS ${TARGET}
    )
endfunction()