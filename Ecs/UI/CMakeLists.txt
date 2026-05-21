include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::UI
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Graphics::Core
    NovelRT::UI

  SOURCES
    PRIVATE
      UISystem.cpp

  HEADERS
    PUBLIC
      include/NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp
      include/NovelRT/Ecs/UI/Components/UIText.hpp
      include/NovelRT/Ecs/UI/Components/UIButton.hpp
      include/NovelRT/Ecs/UI/Components/UISpriteButton.hpp
      include/NovelRT/Ecs/UI/Components/UIClickEvent.hpp
      include/NovelRT/Ecs/UI/UISystem.hpp
      include/NovelRT/Ecs/UI/EcsUIBuilder.hpp
)
