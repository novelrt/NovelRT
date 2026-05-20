include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::UI
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::UI
    NovelRT::Graphics::Core

  SOURCES
    PRIVATE
      empty.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp
      include/NovelRT/Ecs/UI/Components/UIText.hpp
      include/NovelRT/Ecs/UI/Components/UIButton.hpp
      include/NovelRT/Ecs/UI/Components/UISpriteButton.hpp
)
