#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/SecondaryCmdListInfo.hpp>

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>

namespace NovelRT::Ecs::UI
{
    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class UISystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>> _uiProvider;
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _gfxDevice; 
        NovelRT::Ecs::Graphics::Components::RenderPassId _renderPassId;
        std::optional<EntityId> _submissionSemaphoreEntity;
        bool _firstSpin = true;

    public:
        UISystem(std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>> uiProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> gfxDevice)
            : _uiProvider(std::move(uiProvider)),
            _gfxDevice(std::move(gfxDevice)),
            _renderPassId(-1)
        {
        }

        void Update(Timing::Timestamp delta, Catalogue catalogue) override
        {
            if (_renderPassId == -1u)
            {
                return;
            }

            auto [renderPasses, commandLists, trackedSemaphores, graph] = catalogue.GetComponentViews<
            Graphics::Components::RenderPass<TGraphicsBackend>, Graphics::Components::BuiltCommandList<TGraphicsBackend>,
            Graphics::Components::TrackedSemaphore<TGraphicsBackend>, Ecs::Components::EntityGraphComponent>();

            auto uiContext = _gfxDevice->CreateGraphicsContext();

            if(!_submissionSemaphoreEntity.has_value())
            {
                _submissionSemaphoreEntity = catalogue.CreateEntity();
            }

            // auto* descriptorSetArray = new std::shared_ptr<
            //     NovelRT::Graphics::GraphicsDescriptorSet<TGraphicsBackend>>[1];
            // size_t descriptorSetIndex = 0;

            if(_firstSpin)
            {
                auto uploadEntityId = catalogue.CreateEntity();
                auto uploadCmdList = uiContext->CreateCmdList();
                _uiProvider->UploadFontData(uploadCmdList);
                _firstSpin = false;
                Graphics::Components::BuiltCommandList<TGraphicsBackend> uploadCmdListComp{
                .commandList =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(uploadCmdList)};
                commandLists.AddComponent(uploadEntityId, uploadCmdListComp);
                return;
            }
            
            auto currentCmdList =
                    uiContext->CreateCmdList(std::optional<NovelRT::Graphics::SecondaryCmdListInfo<TGraphicsBackend>>(
                        {_uiProvider->GetDedicatedRenderPass(), 0}));

            _uiProvider->BeginFrame(NovelRT::Timing::GetSeconds<float>(delta));
            //do all our imgui calls here
            _uiProvider->EndFrame();

            auto uploadCmdList =
                    uiContext->CreateCmdList();

            //upload data to gpu
            auto uploadEntityId = catalogue.CreateEntity();
            _uiProvider->UploadToGPU(uploadCmdList);
            //Graphics::Components::RenderPass<TGraphicsBackend> uploadPass{};
            //uploadPass.renderPassIndex = _renderPassId;

            Graphics::Components::BuiltCommandList<TGraphicsBackend> uploadCmdListComp{
                .commandList =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(uploadCmdList)};

            //renderPasses.AddComponent(uploadEntityId, uploadPass);
            commandLists.AddComponent(uploadEntityId, uploadCmdListComp);

            //call render
            auto entityId = catalogue.CreateEntity();
            _uiProvider->Draw(currentCmdList);

            Graphics::Components::RenderPass<TGraphicsBackend> passComponent{};
            passComponent.renderPassIndex = _renderPassId;

            Graphics::Components::BuiltCommandList<TGraphicsBackend> cmdListComp{
                .commandList =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(currentCmdList)};

            renderPasses.AddComponent(entityId, passComponent);
            commandLists.AddComponent(entityId, cmdListComp);

        }
    
        NovelRT::Ecs::Graphics::Components::RenderPassId& GetAssignedRenderPassId()
        {
            return _renderPassId;
        }
    };
}
