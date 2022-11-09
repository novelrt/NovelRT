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
                       std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider,
                       std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> defaultRenderingSystem)
        : _uiProvider(uiPluginProvider->GetUIProvider()),
          _defaultRenderingSystem(std::move(defaultRenderingSystem))
    {
        auto graphicsDevice = defaultRenderingSystem->GetGraphicsDevice();
        auto resourceManager = resourceManagementPluginProvider->GetResourceLoader();
        _uiProvider->Initialise(windowingPluginProvider->GetWindowingDevice(), inputPluginProvider->GetInputService(), graphicsDevice);

        auto vertexShaderData = resourceManager->LoadShaderSource("ImguiVert.spv");
        auto pixelShaderData = resourceManager->LoadShaderSource("ImguiPixel.spv");


        auto vertexShaderProgram = graphicsDevice->CreateShaderProgram("main", NovelRT::Graphics::ShaderProgramKind::Vertex, vertexShaderData.shaderCode);
        auto pixelShaderProgram = graphicsDevice->CreateShaderProgram("main", NovelRT::Graphics::ShaderProgramKind::Pixel, pixelShaderData.shaderCode);

        std::vector<NovelRT::Graphics::GraphicsPipelineInputElement> elements = {
            NovelRT::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector2F),
                NovelRT::Graphics::GraphicsPipelineInputElementKind::Position, sizeof(Maths::GeoVector2F)),

            NovelRT::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Maths::GeoVector2F),
                NovelRT::Graphics::GraphicsPipelineInputElementKind::TextureCoordinate, sizeof(Maths::GeoVector2F)),

            NovelRT::Graphics::GraphicsPipelineInputElement(
                typeid(NovelRT::Graphics::RGBAColour),
                NovelRT::Graphics::GraphicsPipelineInputElementKind::Colour, sizeof(NovelRT::Graphics::RGBAColour))
        };

        std::vector<NovelRT::Graphics::GraphicsPipelineInput> inputs = {
            NovelRT::Graphics::GraphicsPipelineInput(elements)};

        std::vector<NovelRT::Graphics::GraphicsPipelineResource> resources = {
            NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::ConstantBuffer,
                                                        NovelRT::Graphics::ShaderProgramVisibility::Vertex),

            NovelRT::Graphics::GraphicsPipelineResource(NovelRT::Graphics::GraphicsPipelineResourceKind::Texture,
                                                        NovelRT::Graphics::ShaderProgramVisibility::Pixel),
        };

        auto signature = graphicsDevice->CreatePipelineSignature(NovelRT::Graphics::GraphicsPipelineBlendFactor::SrcAlpha, NovelRT::Graphics::GraphicsPipelineBlendFactor::OneMinusSrcAlpha, inputs, resources);
        _uiPipeline = graphicsDevice->CreatePipeline(signature, vertexShaderProgram, pixelShaderProgram);

        defaultRenderingSystem->UIRenderEvent +=
            [&](auto defaultRenderingSystem, Graphics::DefaultRenderingSystem::UIRenderEventArgs eventArgs)
        {
            DefaultRenderingSystem& renderingSystem = defaultRenderingSystem.get();

            
            /*
            auto cmdListSubmissionInfo = _submissionInfoQueue.front();
            _submissionInfoQueue.pop();

            for (cmdListSubmissionInfo)
            {
                for (int n = 0; n < drawList->CmdBuffer.Size; n++)
                {
                    const ImDrawCmd* drawCmd = &drawList->CmdBuffer[n];
                    auto tex =
                        *reinterpret_cast<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>*>(drawCmd->GetTexID());
                    std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>> resources{
                        eventArgs.frameMatrixConstantBufferRegion, tex};

                    auto primitive = eventArgs.graphicsDevice->CreatePrimitive(
                        _uiPipeline, vertexInfo.GetBackingConcurrentSharedPtr()->gpuVertexRegion,
                        indexInfo.GetBackingConcurrentSharedPtr()->gpuVertexRegion, drawCmd->ElemCount, resources);
                    eventArgs.graphicsContext->Draw(primitive, 1, drawCmd->IdxOffset, drawCmd->VtxOffset, 0);

                }
            }
             */
        };
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        unused(catalogue);
        _uiProvider->BeginFrame(delta.getSecondsDouble());
        Draw(*this, delta, catalogue);
        _uiProvider->EndFrame();

        ImGui::Render();
        const ImDrawData* drawData = ImGui::GetDrawData();

        for (size_t listIndex = 0; listIndex < drawData->CmdListsCount; listIndex++)
        {
            CmdListSubmissionInfo listSubmissionInfo;
            auto drawList = drawData->CmdLists[listIndex];
            auto listIndexStr = std::to_string(listIndex);
            auto queueSizeStr = std::to_string(_submissionInfoQueue.size() + _gpuObjectsToCleanUp.size());
            FutureResult<VertexInfo> vertexInfo = _defaultRenderingSystem->LoadVertexDataRaw<ImDrawVert>(
                std::string("ImGuiVertices").append(queueSizeStr).append("-").append(listIndexStr),
                gsl::span<ImDrawVert>(drawList->VtxBuffer.begin(), drawList->VtxBuffer.size()));
            FutureResult<VertexInfo> indexInfo = _defaultRenderingSystem->LoadVertexDataRaw<ImDrawIdx>(
                std::string("ImGuiIndices").append(queueSizeStr).append("-").append(listIndexStr),
                gsl::span<ImDrawIdx>(drawList->IdxBuffer.begin(), drawList->IdxBuffer.size()));

            listSubmissionInfo.Vertices = vertexInfo;
            listSubmissionInfo.Indices = indexInfo;

            for(auto&& cmd : drawList->CmdBuffer)
            {
                listSubmissionInfo.Cmds.emplace_back(CmdSubmissionInfo{ cmd.VtxOffset, cmd.IdxOffset });
            }

            _submissionInfoQueue.emplace(listSubmissionInfo);
        }
    }
}
