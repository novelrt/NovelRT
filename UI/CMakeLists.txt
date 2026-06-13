include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::UI
DEPENDS
    NovelRT::Exceptions
    NovelRT::Graphics::Core
    NovelRT::Input
    NovelRT::Logging
    
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

# FIXME: Remove this when updating NovelRT::UI
set_target_properties(NovelRT-UI PROPERTIES SKIP_LINTING TRUE)
