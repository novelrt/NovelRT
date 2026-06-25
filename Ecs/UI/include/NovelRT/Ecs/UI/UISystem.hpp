#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/SecondaryCmdListInfo.hpp>

#include <NovelRT/UI/ImGui/ImGuiUIProvider.hpp>

#include <NovelRT/Exceptions/InvalidOperationException.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/EntityGraphView.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Graphics/Components/BuiltCommandList.hpp>
#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Ecs/Graphics/Components/TrackedSemaphore.hpp>
#include <NovelRT/Ecs/Graphics/Components/Camera.hpp>

#include <NovelRT/Ecs/UI/Components/UIElement.hpp>
#include <NovelRT/Ecs/UI/UIComponentType.hpp>

#include <algorithm>
#include <deque>
#include <map>
#include <set>
#include <utility>
#include <vector>

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

        EntityGraphView GetRoot(ComponentView<Ecs::Components::EntityGraphComponent>& view,
                                Catalogue& catalogue,
                                EntityId entity)
        {
            EntityGraphView it{catalogue, entity, view.GetComponent(entity)};
            if (!it.HasParent())
            {
                return it;
            }

            return GetRoot(view, catalogue, it.GetRawComponentData().parent);
        }

        void ParseElementCommands(Catalogue& catalogue, EntityId entity, Ecs::UI::Components::UIElement& element, float scaleX, float scaleY)
        {
            auto [containers, buttons, textView, transforms, clickEvents] =
                catalogue.GetComponentViews<Ecs::UI::Components::UIWidgetContainer, Ecs::UI::Components::UIButton,
                                            Ecs::UI::Components::UIText, Ecs::Components::TransformComponent,
                                            Ecs::UI::Components::UIClickEvent>();

            switch (element.Type)
            {
                case Ecs::UI::UIComponentType::Container:
                {
                    GenerateContainerCommands(catalogue, entity, element, scaleX, scaleY);
                    break;
                }
                case Ecs::UI::UIComponentType::Button:
                {
                    GenerateButtonCommands(catalogue, entity, element, scaleX, scaleY);
                    break;
                }
                case Ecs::UI::UIComponentType::Text:
                {
                    GenerateTextLineCommands(catalogue, entity, element);
                    break;
                }
                default:
                {
                    std::stringstream exceptionValue;
                    exceptionValue << "The UI Component type is undefined for the current element at entity " << entity << ".";
                    throw NovelRT::Exceptions::InvalidOperationException(exceptionValue.str());
                }
            }
        }

        void EnumerateChildren(EntityGraphView& graph,
                               ComponentView<Ecs::UI::Components::UIElement>& view,
                               std::vector<std::pair<EntityId, int32_t>>& inOrder,
                               int32_t currentDepth = 0)
        {
            if (view.HasComponent(graph.GetRawEntityId()))
                inOrder.emplace_back(graph.GetRawEntityId(), currentDepth);

            if (!graph.HasChildren())
                return;

            for (const auto& child : graph.GetOriginalChildren())
            {
                EnumerateChildren(child.get(), view, inOrder, currentDepth + 1);
            }
        }

        void GenerateContainerCommands(Catalogue& catalogue, EntityId entity, Ecs::UI::Components::UIElement&, float scaleX, float scaleY)
        {
            auto [containers, transforms] =
                catalogue.GetComponentViews<Ecs::UI::Components::UIWidgetContainer,Ecs::Components::TransformComponent>();

            Ecs::Components::TransformComponent transform{};
            Ecs::UI::Components::UIWidgetContainer container{};

            if (containers.TryGetComponent(entity, container) &&
                transforms.TryGetComponent(entity, transform))
            {
                ImGui::SetNextWindowSize(
                    ImVec2(transform.scale.x * scaleX, transform.scale.y * scaleY));
                ImGui::SetNextWindowPos(
                    ImVec2(transform.position.x * scaleX, transform.position.y * scaleY));
                ImGui::Begin(container.title->c_str(), NULL,
                                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            }
        }

        void GenerateButtonCommands(Catalogue& catalogue, EntityId entity, Ecs::UI::Components::UIElement&, float scaleX, float scaleY)
        {
            auto [buttons, transforms, clickEvents] =
                catalogue.GetComponentViews<Ecs::UI::Components::UIButton,
                                            Ecs::Components::TransformComponent,
                                            Ecs::UI::Components::UIClickEvent>();

            Ecs::UI::Components::UIButton button{};
            Ecs::Components::TransformComponent transform{};

            if (buttons.TryGetComponent(entity, button) &&
                transforms.TryGetComponent(entity, transform))
            {
                // Gotta push styling first, then call button
                ImGui::PushStyleColor(ImGuiCol_Button,
                                        ImVec4(button.bgColour.getRScalar(), button.bgColour.getGScalar(),
                                                button.bgColour.getBScalar(), button.bgColour.getAScalar()));

                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(button.hoveredColour.getRScalar(),
                                                                        button.hoveredColour.getGScalar(),
                                                                        button.hoveredColour.getBScalar(),
                                                                        button.hoveredColour.getAScalar()));

                ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                        ImVec4(button.activeColour.getRScalar(), button.activeColour.getGScalar(),
                                                button.activeColour.getBScalar(),
                                                button.activeColour.getAScalar()));

                ImGui::PushStyleColor(ImGuiCol_Text,
                                        ImVec4(button.textColour.getRScalar(), button.textColour.getGScalar(),
                                                button.textColour.getBScalar(), button.textColour.getAScalar()));

                ImGui::SetCursorPos(
                    ImVec2(transform.position.x * scaleX, transform.position.y * scaleY));

                if (ImGui::Button(button.label->c_str(),
                                    ImVec2(transform.scale.x * scaleX, transform.scale.y * scaleY)))
                {
                    Ecs::UI::Components::UIClickEvent clickEvent{};
                    clickEvent.eventId = button.eventId;
                    clickEvents.AddComponent(entity, clickEvent);
                }

                // Remove the styling lest there be demons ahead... or oddities.
                ImGui::PopStyleColor(4);
            }
        }

        void GenerateTextLineCommands(Catalogue& catalogue, EntityId entity, Ecs::UI::Components::UIElement&)
        {
            auto [textView] = catalogue.GetComponentViews<Ecs::UI::Components::UIText>();

            Ecs::UI::Components::UIText text{};

            if (textView.TryGetComponent(entity, text))
            {
                // same pattern - push style, write, pop style;
                ImGui::PushStyleColor(ImGuiCol_Text,
                                        ImVec4(text.colour.getRScalar(), text.colour.getGScalar(),
                                                text.colour.getBScalar(), text.colour.getAScalar()));

                ImGui::Text("%s", text.textValue->c_str());

                ImGui::PopStyleColor();
            }
        }


        void Render(Catalogue& catalogue)
        {
            auto [renderPasses, commandLists, trackedSemaphores] =
                catalogue.GetComponentViews<Graphics::Components::RenderPass<TGraphicsBackend>,
                                            Graphics::Components::BuiltCommandList<TGraphicsBackend>,
                                            Graphics::Components::TrackedSemaphore<TGraphicsBackend>>();

            // create upload command list
            auto uiContext = _gfxDevice->CreateGraphicsContext();
            auto uploadCmdList = uiContext->CreateCmdList();

            // upload data to gpu
            if (_uiProvider->UploadToGPU(uploadCmdList))
            {
                // if we have data to upload to the gpu, then submit the commands.
                std::vector<std::shared_ptr<NovelRT::Graphics::GraphicsCmdList<TGraphicsBackend>>> lists{uploadCmdList};

                // create the semaphore to signal when uploading
                std::vector<
                    std::pair<std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>, uint64_t>>
                    uploadSemaphores{std::make_pair(_uploadSemaphore, ++_submittedUploads)};

                _gfxDevice->QueueSubmit(lists, uploadSemaphores);

                // Create a tracked semaphore that will wait on the upload semaphore
                Graphics::Components::TrackedSemaphore<TGraphicsBackend> newUploadTracker{
                    .semaphore =
                        new std::shared_ptr<NovelRT::Graphics::GraphicsSemaphore<TGraphicsBackend>>(_uploadSemaphore),
                    .signalValue = _submittedUploads};

                // Create unique id for tracking upload
                auto uploadId = catalogue.CreateEntity();

                // add upload semaphore to tracked catalogue
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

        void ProcessComponents(Timing::Timestamp delta, Catalogue& catalogue)
        {
            // 1. Start frame unanimously - this is for debug/metric windows
            _uiProvider->BeginFrame(NovelRT::Timing::GetSeconds<float>(delta));

            auto [graph, elementView, camView] =
                catalogue.GetComponentViews<Ecs::Components::EntityGraphComponent, Ecs::UI::Components::UIElement, Graphics::Components::Camera>();

            // 2. Determine the order in which we should enumerate the entities based on... something?
            std::map<EntityId, Ecs::UI::Components::UIElement> elements{};
            std::set<EntityId> rootEntities{};
            std::vector<EntityGraphView> roots{};
            std::vector<std::pair<EntityId, int32_t>> ordered{};

            for (auto [entity, element] : elementView)
            {
                auto [iterator, inserted] = elements.try_emplace(entity);
                iterator->second = element;

                if (graph.HasComponent(entity))
                {
                    auto root = GetRoot(graph, catalogue, entity);
                    auto [it, insertedTwo] = rootEntities.insert(root.GetRawEntityId());
                    if (insertedTwo)
                        roots.emplace_back(std::move(root));
                }
            }

            if (elements.empty())
            {
                // end the frame now so at least debug stuff displays
                _uiProvider->EndFrame();
                return;
            }

            // 3. Enumerate the child elements
            for (auto& root : roots)
            {
                EnumerateChildren(root, elementView, ordered);
            }

            // 4a - SCALE EVERYTHING
            //  This lets us make sure that imgui tracks with the screen properly - otherwise it does not adjust
            //  with other elements.
            auto& io = ::ImGui::GetIO();

            float refWidth = io.DisplaySize.x;
            float refHeight = io.DisplaySize.y;

            for (auto [entity, camera]: camView)
            {
                if (camera.isScreenSpace)
                {
                    refWidth = static_cast<float>(camera.referenceResolutionWidth);
                    refHeight = static_cast<float>(camera.referenceResolutionHeight);
                    break;
                }
            }

            float scaleX = io.DisplaySize.x / refWidth;
            float scaleY = io.DisplaySize.y / refHeight;
            //float avgScale = (scaleX + scaleY) * 0.5f;
            //io.FontGlobalScale *= avgScale;  // font scaling

            // 4b. write Imgui commands
            std::vector<std::pair<EntityId, int32_t>> containers{};

            for (auto& [entity, depth] : ordered)
            {
                while (!containers.empty() && containers.back().second >= depth)
                {
                    ImGui::End();
                    containers.pop_back();
                }

                auto element = elements.find(entity);

                if (element != elements.end())
                {
                    ParseElementCommands(catalogue, entity, element->second, scaleX, scaleY);

                    if (element->second.Type == UIComponentType::Container)
                    {
                        containers.emplace_back(entity, depth);
                    }
                }
            }

            while (!containers.empty())
            {
                ImGui::End();
                containers.pop_back();
            }

            // 5. End imgui frame so all items are writen to draw data
            _uiProvider->EndFrame();
        }

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
            // if the renderpass' Id is not assigned, don't perform any updates.
            if (_renderPassId == 0ULL)
            {
                return;
            }

            ProcessComponents(delta, catalogue);

            Render(catalogue);
        }

        NovelRT::Ecs::Graphics::Components::RenderPassId& GetAssignedRenderPassId()
        {
            return _renderPassId;
        }
    };
}
