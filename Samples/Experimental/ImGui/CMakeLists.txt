include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(EXECUTABLE NovelRT::Samples::Experimental::ImGui
  DEPENDS
    NovelRT::Graphics
    NovelRT::Graphics::Vulkan
    NovelRT::Input
    NovelRT::UI
    NovelRT::Windowing

  SOURCES
    PRIVATE
      main.cpp

  RESOURCES
    PUBLIC
      Resources/Fonts/Raleway-Regular.ttf
      Resources/Shaders/imgui_frag.spv
      Resources/Shaders/imgui_vert.spv
      Resources/Shaders/vulkanrenderfrag.spv
      Resources/Shaders/vulkanrendervert.spv)
