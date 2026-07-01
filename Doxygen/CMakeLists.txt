function(append_string_to_first_list_element APPEND_ARGS_INPUT APPEND_ARGS_APPENDATURE APPEND_OUT)
  string(REPLACE "\n" ";" APPEND_LISTED_STRING ${APPEND_ARGS_INPUT})
  list(GET APPEND_LISTED_STRING 0 APPEND_LISTED_STRING_FIRST)
  set(APPEND_LISTED_STRING_FIRST_TAGGED "${APPEND_LISTED_STRING_FIRST} ${APPEND_ARGS_APPENDATURE}")

  list(REMOVE_AT APPEND_LISTED_STRING 0)
  list(INSERT APPEND_LISTED_STRING 0 "${APPEND_LISTED_STRING_FIRST_TAGGED}")

  list(JOIN APPEND_LISTED_STRING "\n" APPEND_FINAL)
  set(${APPEND_OUT} ${APPEND_FINAL} PARENT_SCOPE)
endfunction()

if (NOT DEFINED DOXYGEN_OUTPUT_DIRECTORY)
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Doxygen)
else()
  message("Doxygen output directory defined as: ${DOXYGEN_OUTPUT_DIRECTORY}")
  set(DOXYGEN_HTML_OUTPUT ${DOXYGEN_OUTPUT_DIRECTORY})
endif()

set(DOCS_MAINPAGE
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/LICENCE.md
        ${PROJECT_SOURCE_DIR}/LICENCE-DIST.md
        ${PROJECT_SOURCE_DIR}/CODE_OF_CONDUCT.md
        )

foreach(docFile ${DOCS_MAINPAGE})
  file(READ ${docFile} TEMP_DOC_FILE_CONTENTS)
  get_filename_component(TEMP_DOC_FILE_NAME ${docFile} NAME)
  file(REMOVE ${DOXYGEN_OUTPUT_DIRECTORY}/${TEMP_DOC_FILE_NAME})

  if(${TEMP_DOC_FILE_NAME} STREQUAL "README.md")
    append_string_to_first_list_element("${TEMP_DOC_FILE_CONTENTS}" "{#mainpage}" TEMP_DOC_FILE_CONTENTS)
    string(REPLACE "(CODE_OF_CONDUCT.md)" "(@ref conduct)" TEMP_DOC_FILE_CONTENTS ${TEMP_DOC_FILE_CONTENTS})
    string(REPLACE "(LICENCE.md)" "(@ref licence)" TEMP_DOC_FILE_CONTENTS ${TEMP_DOC_FILE_CONTENTS})
    string(REPLACE "(LICENCE-DIST.md)" "(@ref licenceDist)" TEMP_DOC_FILE_CONTENTS ${TEMP_DOC_FILE_CONTENTS})
  endif()
  if(${TEMP_DOC_FILE_NAME} STREQUAL "CODE_OF_CONDUCT.md")
    append_string_to_first_list_element("${TEMP_DOC_FILE_CONTENTS}" "{#conduct}" TEMP_DOC_FILE_CONTENTS)
  endif()
  if(${TEMP_DOC_FILE_NAME} STREQUAL "LICENCE.md")
    append_string_to_first_list_element("${TEMP_DOC_FILE_CONTENTS}" "{#licence}" TEMP_DOC_FILE_CONTENTS)
  endif()
  if(${TEMP_DOC_FILE_NAME} STREQUAL "LICENCE-DIST.md")
    append_string_to_first_list_element("${TEMP_DOC_FILE_CONTENTS}" "{#licenceDist}" TEMP_DOC_FILE_CONTENTS)
  endif()

  file(WRITE ${DOXYGEN_OUTPUT_DIRECTORY}/${TEMP_DOC_FILE_NAME} "${TEMP_DOC_FILE_CONTENTS}")
endforeach()

set(DOXYGEN_PROJECT_LOGO novel-chan-header_doxy.jpg)

set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
set(DOXYGEN_JAVADOC_BANNER YES)
set(DOXYGEN_EXTRACT_PRIV_VIRTUAL YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_CASE_SENSE_NAMES NO)

set(DOXYGEN_HTML_COLORSTYLE_HUE 260)
set(DOXYGEN_HTML_COLORSTYLE_SAT 245)
set(DOXYGEN_HTML_COLORSTYLE_GAMMA 120)

set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_INTERACTIVE_SVG YES)

set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_MATHJAX_VERSION MathJax_3)
set(DOXYGEN_MATHJAX_EXTENSIONS ams)
set(DOXYGEN_HTML_EXTRA_STYLESHEET left-align-mathjax.css)

set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md CODE_OF_CONDUCT.md LICENCE.md LICENCE-DIST.md")

doxygen_add_docs(Doxygen
        ALL
        COMMENT "Generating documentation"
        ${DOXYGEN_OUTPUT_DIRECTORY}/README.md
        ${DOXYGEN_OUTPUT_DIRECTORY}/CODE_OF_CONDUCT.md
        ${DOXYGEN_OUTPUT_DIRECTORY}/LICENCE.md
        ${DOXYGEN_OUTPUT_DIRECTORY}/LICENCE-DIST.md
        ${PROJECT_SOURCE_DIR}/Audio/Core/include
        ${PROJECT_SOURCE_DIR}/Audio/OpenAL/include
        ${PROJECT_SOURCE_DIR}/Ecs/Audio/include
        ${PROJECT_SOURCE_DIR}/Ecs/Core/include
        ${PROJECT_SOURCE_DIR}/Ecs/Graphics/include
        ${PROJECT_SOURCE_DIR}/Ecs/Scripting/Core/include
        ${PROJECT_SOURCE_DIR}/Ecs/Scripting/Graphics/include
        ${PROJECT_SOURCE_DIR}/Ecs/Scripting/UI/include
        ${PROJECT_SOURCE_DIR}/Ecs/UI/include
        ${PROJECT_SOURCE_DIR}/Exceptions/include
        ${PROJECT_SOURCE_DIR}/Graphics/Core/include
        ${PROJECT_SOURCE_DIR}/Graphics/Vulkan/include
        ${PROJECT_SOURCE_DIR}/Input/Core/include
        ${PROJECT_SOURCE_DIR}/Input/Glfw/include
        ${PROJECT_SOURCE_DIR}/Logging/include
        ${PROJECT_SOURCE_DIR}/Maths/include
        ${PROJECT_SOURCE_DIR}/ResourceManagement/Core/include
        ${PROJECT_SOURCE_DIR}/ResourceManagement/Desktop/include
        ${PROJECT_SOURCE_DIR}/Scripting/Core/include
        ${PROJECT_SOURCE_DIR}/Threading/include
        ${PROJECT_SOURCE_DIR}/Timing/include
        ${PROJECT_SOURCE_DIR}/UI/include
        ${PROJECT_SOURCE_DIR}/Utilities/include
        ${PROJECT_SOURCE_DIR}/Windowing/Core/include
        ${PROJECT_SOURCE_DIR}/Windowing/Glfw/include
        )
