#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/GraphicsComponents.hpp>
#include <NovelRT/Ecs/DefaultComponentTypes.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>

#include <algorithm>
#include <map>
#include <set>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class SpriteRendererSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;

    public:
        void Update(Timing::Timestamp delta, Catalogue catalogue) override
        {
            auto [sprites, renderPasses, commandLists] = catalogue.GetComponentViews<Sprite, RenderPass, BuiltCommandList<TGraphicsBackend>>();

            for (auto [entity, sprite] : sprites)
            {
                auto context = _graphicsDevice->CreateGraphicsContext();
                auto cmdList = context->BeginFrame();

                // rendering la la la la
                context->EndFrame();

                BuiltCommandList<TGraphicsBackend> temp{new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>};
                temp.commandList = cmdList;
                renderPasses.AddComponent(entity, {1});
                commandLists.AddComponent(entity, temp);
            }
        }
    }
}
