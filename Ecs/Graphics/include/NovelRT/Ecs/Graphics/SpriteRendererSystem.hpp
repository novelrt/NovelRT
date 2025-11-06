#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Graphics/GraphicsDevice.hpp>
#include <NovelRT/Graphics/GraphicsContext.hpp>
#include <NovelRT/Graphics/GraphicsCmdList.hpp>

#include <NovelRT/Graphics/NullGraphicsBackend.hpp> // God is dead and so are my preferred editors - Matt J.

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class SpriteRendererSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _graphicsDevice;

    public:
        void Update(Timing::Timestamp /*delta*/, Catalogue catalogue) override
        {
            auto [sprites, renderPasses, commandLists] = catalogue.GetComponentViews<Components::Sprite, Components::RenderPass, Components::BuiltCommandList<TGraphicsBackend>>();

            for (auto [entity, sprite] : sprites)
            {
                auto context = _graphicsDevice->CreateGraphicsContext();
                std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>> cmdList = context->BeginFrame();

                // rendering la la la la
                cmdList->CmdBeginRenderPass(nullptr, nullptr, {});

                context->EndFrame();

                Components::BuiltCommandList<TGraphicsBackend> temp{new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>};

                temp.commandList = cmdList;
                renderPasses.AddComponent(entity, {1});
                commandLists.AddComponent(entity, temp);
            }
        }
    };
}
