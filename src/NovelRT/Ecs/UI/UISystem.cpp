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
          _defaultRenderingSystem(std::move(defaultRenderingSystem)),
          _uiPipeline(nullptr),
          _submissionInfoListMutex(),
          _submissionInfoListQueue{},
          _gpuObjectsToCleanUp{},
          _drawCallCounter(0)
    {
        auto graphicsDevice = _defaultRenderingSystem->GetGraphicsDevice();
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

        _defaultRenderingSystem->UIRenderEvent +=
            [&](auto , Graphics::DefaultRenderingSystem::UIRenderEventArgs eventArgs)
        {
            _primitivesForFrame.clear();

            for (auto&& cmdList : _gpuObjectsToCleanUp)
            {
                _defaultRenderingSystem->DeleteVertexData(cmdList.Vertices.GetBackingConcurrentSharedPtr());
                _defaultRenderingSystem->DeleteIndexData(cmdList.Indices.GetBackingConcurrentSharedPtr());
            }

            _gpuObjectsToCleanUp.clear();

            std::vector<CmdListSubmissionInfo> finalCmdListSubmissionInfosForFrame{};

            if (!_submissionInfoListQueue.empty())
            {
                std::scoped_lock lock(_submissionInfoListMutex);
                auto cmdListSubmissionInfos = _submissionInfoListQueue.front();

                auto& drawData = cmdListSubmissionInfos.at(0);
                if (drawData.Vertices.IsValueCreated() && drawData.Indices.IsValueCreated())
                {
                    finalCmdListSubmissionInfosForFrame = cmdListSubmissionInfos;
                    _submissionInfoListQueue.pop();
                }
            }

            if (finalCmdListSubmissionInfosForFrame.empty())
            {
                return;
            }

            for(auto&& cmdListSubmissionInfo : finalCmdListSubmissionInfosForFrame)
            {
                for (auto&& drawCmd : cmdListSubmissionInfo.Cmds)
                {
                    std::vector<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>>
                        resources{eventArgs.frameMatrixConstantBufferRegion, drawCmd.textureData};

                    auto primitive = eventArgs.graphicsDevice->CreatePrimitive(
                        _uiPipeline, cmdListSubmissionInfo.Vertices.GetBackingConcurrentSharedPtr()->gpuVertexRegion, 0,
                        cmdListSubmissionInfo.Indices.GetBackingConcurrentSharedPtr()->gpuIndexRegion, 2, resources);
                    eventArgs.graphicsContext->Draw(primitive, 1, drawCmd.indexOffset, static_cast<int32_t>(drawCmd.vertexOffset), 0);

                    _primitivesForFrame.emplace_back(primitive);
                }

                _gpuObjectsToCleanUp.emplace_back(cmdListSubmissionInfo);
            }
        };

/*
        // TEST CODE - DELETE WHEN DONE

        Draw += [&](auto, auto, auto) {
            ImGui::Text("Hello, NovelRT!");
        };

        // END TEST CODE
        */
    }

    void UISystem::Update(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
        unused(catalogue);
        _uiProvider->BeginFrame(delta.getSecondsDouble());
        Draw(*this, delta, catalogue);
        _uiProvider->EndFrame();

        ImGui::Render();
        const ImDrawData* drawData = ImGui::GetDrawData();

        std::vector<CmdListSubmissionInfo> listSubmissionInfos{};

        for (size_t listIndex = 0; listIndex < drawData->CmdListsCount; listIndex++)
        {
            CmdListSubmissionInfo listSubmissionInfo;
            auto drawList = drawData->CmdLists[listIndex];
            auto drawCallCounterStr =_drawCallCounter++;
            FutureResult<VertexInfo> vertexInfo = _defaultRenderingSystem->LoadVertexDataRaw<ImDrawVert>(
                "ImGuiVertices" + std::to_string(drawCallCounterStr),
                gsl::span<ImDrawVert>(drawList->VtxBuffer.begin(), drawList->VtxBuffer.size()));
            FutureResult<IndexInfo> indexInfo = _defaultRenderingSystem->LoadIndexDataRaw<ImDrawIdx>(
                "ImGuiIndices" + std::to_string(drawCallCounterStr),
                gsl::span<ImDrawIdx>(drawList->IdxBuffer.begin(), drawList->IdxBuffer.size()), IndexIntegerKind::UInt16);

            listSubmissionInfo.Vertices = vertexInfo;
            listSubmissionInfo.Indices = indexInfo;

            for(auto&& cmd : drawList->CmdBuffer)
            {
                listSubmissionInfo.Cmds.emplace_back(CmdSubmissionInfo{ cmd.VtxOffset, cmd.IdxOffset, cmd.ElemCount, *reinterpret_cast<NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource>*>(cmd.GetTexID()) });
            }

            listSubmissionInfos.emplace_back(listSubmissionInfo);
        }

        if (listSubmissionInfos.empty())
        {
            return;
        }

        std::scoped_lock lock(_submissionInfoListMutex);
        _submissionInfoListQueue.emplace(listSubmissionInfos);
    }
}
