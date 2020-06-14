# More information on how this was made can be found at https://quantumlytangled.com/generating-doxygen-documentation-for-cpp-using-cmake/

find_package(Doxygen QUIET)

set(DOCS_IMAGES
  novel-chan_doxy.png
)

set(DOCS_MAINPAGE
  ${CMAKE_SOURCE_DIR}/README.md
  ${CMAKE_SOURCE_DIR}/LICENCE.md
  ${CMAKE_SOURCE_DIR}/CODE_OF_CONDUCT.md
)

set(DOCS_RESOURCES
  ${DOCS_IMAGES}
)

function(APPEND_STRING_TO_FIRST_LIST_ELEMEMT APPEND_ARGS_INPUT APPEND_ARGS_APPENDATURE APPEND_OUT)
  string(REPLACE "\n" ";" APPEND_LISTED_STRING ${APPEND_ARGS_INPUT})
  list(GET APPEND_LISTED_STRING 0 APPEND_LISTED_STRING_FIRST)
  set(APPEND_LISTED_STRING_FIRST_TAGGED "${APPEND_LISTED_STRING_FIRST} ${APPEND_ARGS_APPENDATURE}")

  list(REMOVE_AT APPEND_LISTED_STRING 0)
  list(INSERT APPEND_LISTED_STRING 0 "${APPEND_LISTED_STRING_FIRST_TAGGED}")

  list(JOIN APPEND_LISTED_STRING "\n" APPEND_FINAL)
  set(${APPEND_OUT} ${APPEND_FINAL} PARENT_SCOPE)
endfunction()

if (DOXYGEN_FOUND)
  set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/include/)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
  set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
  set(DOXYGEN_FAKE_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/__index.html) 
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(DOXYFILE_OUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)

  set(DOXYGEN_PROJECT_VERSION ${CMAKE_PROJECT_VERSION})
  set(DOXYGEN_PROJECT_LOGO ${DOXYGEN_OUTPUT_DIR}/novel-chan_doxy.png)

  list(JOIN DOCS_MAINPAGE " " DOCS_MAINPAGE_STRING)
  string(REPLACE "${CMAKE_SOURCE_DIR}" "${DOXYGEN_OUTPUT_DIR}" DOCS_MAINPAGE_STRING ${DOCS_MAINPAGE_STRING})

  #Replace variables inside @@ with the current values
  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
  file(COPY ${DOCS_RESOURCES} DESTINATION ${DOXYGEN_OUTPUT_DIR})

  foreach(docFile ${DOCS_MAINPAGE})
    file(READ ${docFile} TEMP_DOC_FILE_CONTENTS)
    get_filename_component(TEMP_DOC_FILE_NAME ${docFile} NAME)

    if(${TEMP_DOC_FILE_NAME} STREQUAL "README.md")
      APPEND_STRING_TO_FIRST_LIST_ELEMEMT("${TEMP_DOC_FILE_CONTENTS}" "{#mainpage}" TEMP_DOC_FILE_CONTENTS)
    endif()

    file(WRITE ${DOXYGEN_OUTPUT_DIR}/${TEMP_DOC_FILE_NAME} "${TEMP_DOC_FILE_CONTENTS}") 
  endforeach()

  add_custom_command(
                     OUTPUT
                       ${DOXYGEN_INDEX_FILE}
                       ${DOXYGEN_FAKE_INDEX_FILE}
                     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                     MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                     COMMENT "Generating docs")

  add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
else ()
	message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
