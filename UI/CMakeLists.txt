include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::UI
  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/UI/ImGui/ImGuiUIProvider.hpp

  LINK_LIBRARIES
    PUBLIC
      imgui::imgui
)
