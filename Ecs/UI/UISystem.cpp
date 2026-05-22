#include <NovelRT/Ecs/UI/Components/UIButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIClickEvent.hpp>
#include <NovelRT/Ecs/UI/Components/UISpriteButton.hpp>
#include <NovelRT/Ecs/UI/Components/UIText.hpp>
#include <NovelRT/Ecs/UI/Components/UIWidgetContainer.hpp>
#include <NovelRT/Ecs/UI/UISystem.hpp>


namespace NovelRT::Ecs::UI
{
    template<typename TGraphicsBackend, typename TWindowingBackend, typename TInputBackend>
    void UISystem<TGraphicsBackend, TWindowingBackend, TInputBackend>::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
    {
        unused(catalogue);
        if(_firstSpin)
        {
            _uiProvider->UploadFontData();
            _firstSpin = false;
        }



    }
}
