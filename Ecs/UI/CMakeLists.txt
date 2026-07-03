include(NovelRTBuildSystem)

NovelRTBuildSystem_DeclareModule(LIBRARY NovelRT::Ecs::UI
  DEPENDS
    NovelRT::Ecs::Core
    NovelRT::Ecs::Graphics
    NovelRT::Graphics::Core
    NovelRT::UI
    NovelRT::Input::Core

  SOURCES
    UISystem.cpp

  HEADERS
    include/NovelRT/Ecs/UI/Components/UIElement.hpp
    include/NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp
    include/NovelRT/Ecs/UI/Components/UIText.hpp
    include/NovelRT/Ecs/UI/Components/UIButton.hpp
    include/NovelRT/Ecs/UI/Components/UIClickEvent.hpp
    include/NovelRT/Ecs/UI/UISystem.hpp
    include/NovelRT/Ecs/UI/EcsUIBuilder.hpp
    include/NovelRT/Ecs/UI/UIComponentType.hpp
)
