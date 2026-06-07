#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/SecondaryCmdListInfo.hpp>

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

namespace NovelRT::Ecs::UI
{
    template<typename TGraphicsBackend, typename TInputBackend, typename TWindowingBackend>
    class UISystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>
            _uiProvider;
        std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> _gfxDevice;
        NovelRT::Ecs::Graphics::Components::RenderPassId _renderPassId;
        std::optional<EntityId> _drawSemaphoreEntity;
        bool _firstSpin = true;
        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _uploadSemaphore;
        std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>> _drawSemaphore;
        uint64_t _submittedUploads;
        uint64_t _frameCounter{0};

    public:
        UISystem(
            std::shared_ptr<NovelRT::UI::ImGui::ImGuiUIProvider<TGraphicsBackend, TInputBackend, TWindowingBackend>>
                uiProvider,
            std::shared_ptr<NovelRT::Graphics::GraphicsDevice<TGraphicsBackend>> gfxDevice)
            : _uiProvider(std::move(uiProvider)),
              _gfxDevice(std::move(gfxDevice)),
              _renderPassId(0ULL),
              _uploadSemaphore(_gfxDevice->CreateSemaphore(0)),
              _drawSemaphore(_gfxDevice->CreateSemaphore(0)),
              _submittedUploads(0)
        {
        }

        void Update(Timing::Timestamp delta, Catalogue catalogue) override
        {
            if (_renderPassId == 0ULL)
            {
                return;
            }

            auto [renderPasses, commandLists, trackedSemaphores, graph] =
                catalogue.GetComponentViews<Graphics::Components::RenderPass<TGraphicsBackend>,
                                            Graphics::Components::BuiltCommandList<TGraphicsBackend>,
                                            Graphics::Components::TrackedSemaphore<TGraphicsBackend>,
                                            Ecs::Components::EntityGraphComponent>();

            auto uiContext = _gfxDevice->CreateGraphicsContext();

            _uiProvider->BeginFrame(NovelRT::Timing::GetSeconds<float>(delta));
            // do all our imgui calls here
            _uiProvider->EndFrame();

            auto uploadCmdList = uiContext->CreateCmdList();

            // upload data to gpu
            if (_uiProvider->UploadToGPU(uploadCmdList))
            {
                std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> lists{uploadCmdList};

                // create the semaphore to signal when uploading
                std::vector<std::pair<std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>,
                                    uint64_t>>
                    uploadSemaphores{std::make_pair(_uploadSemaphore, ++_submittedUploads)};

                _gfxDevice->QueueSubmit(lists, uploadSemaphores);

                // Create a tracked semaphore that will wait on the upload semaphore
                Graphics::Components::TrackedSemaphore<TGraphicsBackend> newUploadTracker{
                    .semaphore =
                        new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(_uploadSemaphore),
                    .signalValue = _submittedUploads};

                // Create unique id for tracking upload
                auto uploadId = catalogue.CreateEntity();

                //add upload semaphore to tracked catalogue
                trackedSemaphores.AddComponent(uploadId, newUploadTracker);

                // create entity id for drawing
                auto entityId = catalogue.CreateEntity();

                // check if draw semaphore has value
                // if not, create one
                if (!_drawSemaphoreEntity.has_value())
                {
                    _drawSemaphoreEntity = catalogue.CreateEntity();
                }

                // create the tracked (signal) semaphore component for the draw semaphore
                Graphics::Components::TrackedSemaphore<TGraphicsBackend> signalSemaComponent{};
                signalSemaComponent.isWaitSemaphore = false;
                signalSemaComponent.semaphore =
                    new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(_drawSemaphore);
                signalSemaComponent.signalValue = ++_frameCounter;

                // add it to the catalogue
                trackedSemaphores.AddComponent(_drawSemaphoreEntity.value(), signalSemaComponent);

                // create the draw cmdList
                auto drawCmdList =
                    uiContext->CreateCmdList(std::optional<NovelRT::Graphics::SecondaryCmdListInfo<TGraphicsBackend>>(
                        {_uiProvider->GetDedicatedRenderPass(), 0}));

                drawCmdList->Begin();
                // call render
                _uiProvider->Draw(drawCmdList);
                drawCmdList->End();
                // Create renderpass component
                Graphics::Components::RenderPass<TGraphicsBackend> passComponent{};
                passComponent.renderPassIndex = _renderPassId;

                // create draw lists
                Graphics::Components::BuiltCommandList<TGraphicsBackend> drawLists{
                    .commandList =
                        new std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>(drawCmdList)};

                // add to the catalogue
                renderPasses.AddComponent(entityId, passComponent);
                commandLists.AddComponent(entityId, drawLists);
            }
        }

        NovelRT::Ecs::Graphics::Components::RenderPassId& GetAssignedRenderPassId()
        {
            return _renderPassId;
        }
    };
}
