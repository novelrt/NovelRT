// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <imgui.h>

using namespace NovelRT::Ecs::Graphics;
using namespace NovelRT::Threading;

namespace NovelRT::Ecs::UI
{
    UISystem::UISystem(std::shared_ptr<PluginManagement::IUIPluginProvider> uiPluginProvider,
                       std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                       std::shared_ptr<PluginManagement::IInputPluginProvider> inputPluginProvider,
                       std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> defaultRenderingSystem)
        : _uiProvider(uiPluginProvider->GetUIProvider())
    {
        _uiProvider->Initialise(windowingPluginProvider->GetWindowingDevice(), inputPluginProvider->GetInputService());

        defaultRenderingSystem->UIRenderEvent +=
            [&](auto defaultRenderingSystem, Graphics::DefaultRenderingSystem::UIRenderEventArgs eventArgs)
        {
            DefaultRenderingSystem& renderingSystem = defaultRenderingSystem.get();
            auto pipeline = renderingSystem.GetExistingPipelineInfo("default");

            ImGui::Render();
            const ImDrawData* drawData = ImGui::GetDrawData();

            for (size_t listIndex = 0; listIndex < drawData->CmdListsCount; listIndex++)
            {
                auto listIndexStr = std::to_string(listIndex);
                auto drawList = drawData->CmdLists[listIndex];
                FutureResult<VertexInfo> vertexInfo = renderingSystem.LoadVertexDataRaw<ImDrawVert>("ImGuiVertices" + listIndexStr, gsl::span<ImDrawVert>(drawList->VtxBuffer.begin(), drawList->VtxBuffer.size()));
                FutureResult<VertexInfo> indexInfo = renderingSystem.LoadVertexDataRaw<ImDrawIdx>("ImGuiIndices" + listIndexStr, gsl::span<ImDrawIdx>(drawList->IdxBuffer.begin(), drawList->IdxBuffer.size()));



                for (int n = 0; n < drawList->CmdBuffer.Size; n++)
                {
                    const ImDrawCmd* drawCmd = &drawList->CmdBuffer[n];

                    //()drawCmd->GetTexID();
/*
                    auto primitive = eventArgs.graphicsDevice->CreatePrimitive(
                        pipeline->gpuPipeline.GetUnderlyingSharedPtr(), drawCmd-> squareVertexFuture.GetValue().gpuVertexRegion,
                        sizeof(TexturedVertex), dummyRegion, 0, inputResourceRegions);
                    args.graphicsContext->Draw(primitive, 3);
                    */
                }

            }

            /*
            for (int i = 0; i < drawData->CmdListsCount; i++)
            {
                const ImDrawList* drawList = drawData->CmdLists[i];

                for (int n = 0; n < drawList->CmdBuffer.Size; n++)
                {
                    const ImDrawCmd* drawCmd = &drawList->CmdBuffer[n];

                    auto primitive = eventArgs.graphicsDevice->CreatePrimitive(
                        pipeline->gpuPipeline.GetUnderlyingSharedPtr(), drawCmd-> squareVertexFuture.GetValue().gpuVertexRegion,
                        sizeof(TexturedVertex), dummyRegion, 0, inputResourceRegions);
                    args.graphicsContext->Draw(primitive, 3);
                }
            }
             */
        };
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        //UNREFERENCED_PARAMETER(catalogue);

        _uiProvider->BeginFrame(delta.getSecondsDouble());
        Draw(*this, delta, catalogue);
        _uiProvider->EndFrame();
    }
}
