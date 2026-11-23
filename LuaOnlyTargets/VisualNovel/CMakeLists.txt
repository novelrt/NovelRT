include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::LuaOnlyTargets::VisualNovel
  MACOSX_BUNDLE

  DEPENDS
    NovelRT::Ecs
    NovelRT::Ecs::Graphics
    NovelRT::Ecs::Scripting
    NovelRT::ResourceManagement::Desktop

  SOURCES
    main.cpp

  RESOURCES
    Resources/Fonts/Raleway-Regular.ttf
    Resources/Images/Milk.png
    Resources/Images/novel-chan.png
    Resources/Scripts/Sample.lua
    Resources/Shaders/imgui_frag.spv
    Resources/Shaders/imgui_vert.spv
    Resources/Shaders/vulkanrenderfrag.spv
    Resources/Shaders/vulkanrendervert.spv
    Resources/Shaders/SpritePixel.spv
    Resources/Shaders/SpriteVertex.spv
    Resources/VNConfig.json
    Resources/Images/SampleBG.png
)

if(APPLE AND NOVELRT_INSTALL)
  if(DEFINED ENV{CODESIGN_IDENTITY} AND NOT "$ENV{CODESIGN_IDENTITY}" STREQUAL "")
    set(NOVELRT_CODESIGN_IDENTITY "$ENV{CODESIGN_IDENTITY}" CACHE STRING "" FORCE)
  endif()

  if(NOT DEFINED NOVELRT_CODESIGN_IDENTITY)
    # this will cause ad-hoc signing... NOT distributable :/
    # example of valid identity: "Developer ID Application: <Name> (<Team ID>)"
    set(NOVELRT_CODESIGN_IDENTITY "-" CACHE STRING "")
  endif()
  install(CODE "set(novelrtCodesignIdentity [[${NOVELRT_CODESIGN_IDENTITY}]])")
  install(CODE [[
    set(novelrtBundle "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/apps/VisualNovel.app")

    if(novelrtCodesignIdentity STREQUAL "")
      message(FATAL_ERROR "NOVELRT_CODESIGN_IDENTITY is empty - cannot sign")
    endif()
    if(NOT EXISTS "${novelrtBundle}")
      message(FATAL_ERROR "No bundle at '${novelrtBundle}'")
    endif()

    find_program(novelrtCodesign codesign REQUIRED)

    set(novelrtCodesignArgs --force --sign "${novelrtCodesignIdentity}")
    if(novelrtCodesignIdentity MATCHES "^Developer ID Application")
      # we have the right identity to enable hardended runtime and timestamping
      # the sig for notarization purposes.
      list(APPEND novelrtCodesignArgs --options runtime --timestamp) 
    endif()

    file(GLOB_RECURSE novelrtFrameworkItems LIST_DIRECTORIES false
      "${novelrtBundle}/Contents/Frameworks/*")
    foreach(novelrtItem IN LISTS novelrtFrameworkItems)
      if(IS_SYMLINK "${novelrtItem}")
        continue()
      endif()
      execute_process(
        COMMAND file -b "${novelrtItem}"
        OUTPUT_VARIABLE novelrtFileType
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      if(NOT novelrtFileType MATCHES "Mach-O")
        continue()
      endif()
      execute_process(
        COMMAND "${novelrtCodesign}" ${novelrtCodesignArgs} "${novelrtItem}"
        RESULT_VARIABLE codesignResult
        OUTPUT_VARIABLE codesignOutput
        ERROR_VARIABLE codesignOutput)
      if(NOT codesignResult EQUAL 0)
        message(WARNING "Signing failed - ${codesignOutput}")
      endif()
    endforeach()

    execute_process(
      COMMAND "${novelrtCodesign}" ${novelrtCodesignArgs} "${novelrtBundle}"
      RESULT_VARIABLE codesignResult
      OUTPUT_VARIABLE codesignOutput
      ERROR_VARIABLE codesignOutput)
    if(NOT codesignResult EQUAL 0)
      message(WARNING "Signing failed - ${codesignOutput}")
    endif()

    execute_process(
      COMMAND "${novelrtCodesign}" --verify --deep --strict "${novelrtBundle}"
      RESULT_VARIABLE codesignResult
      OUTPUT_VARIABLE codesignOutput
      ERROR_VARIABLE codesignOutput)
    if(NOT codesignResult EQUAL 0)
      message(WARNING "Signature verification failed - ${codesignOutput}")
    endif()

    message(STATUS "Signed '${novelrtBundle}' with '${novelrtCodesignIdentity}' successfully!")
  ]])
endif()